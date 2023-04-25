#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

#include <llvm/IR/InstIterator.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

namespace {

  class TracePass : public FunctionPass {
  public:
    static inline char ID = 0;

    TracePass(): FunctionPass(ID) {}

    static std::string getStringRepresentation(const Instruction& I) {
      LLVMContext& Ctx = I.getContext();
      std::string s;
      raw_string_ostream os(s);
      os << I;
      return s;
    }

    static FunctionCallee getTraceFunction(Module& M, StringRef Name) {
      LLVMContext& Ctx = M.getContext();
      FunctionType *FTy = FunctionType::get(Type::getVoidTy(Ctx), {Type::getInt8PtrTy(Ctx)}, false);
      return M.getOrInsertFunction(Name, FTy);
    }

    bool runOnFunction(Function& F) override {
      LLVMContext& Ctx = F.getContext();
      Module& M = *F.getParent();
      for (Instruction& I : instructions(F)) {
	IRBuilder<> IRB(&I);
	Value *IStr = IRB.CreateGlobalString(getStringRepresentation(I));
	FunctionCallee Callee = getTraceFunction(M, "trace");
	IRB.CreateCall(Callee, {IStr});

      }

      return true;
    }
  };

  RegisterStandardPasses X(PassManagerBuilder::EP_EarlyAsPossible, [] (const PassManagerBuilder&,
								       legacy::PassManagerBase& PM) {
    PM.add(new TracePass());
  });

  RegisterPass<TracePass> Y("TracePass", "Trace Pass");
  
}
