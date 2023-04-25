#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

using namespace llvm;

namespace {

  class SimplePass : public FunctionPass {
  public:
    static inline char ID = 0;

    SimplePass(): FunctionPass(ID) {}

    bool runOnFunction(Function& F) override {
      errs() << F.getName() << "\n";
      return false;
    }
  };

  RegisterStandardPasses X(PassManagerBuilder::EP_EarlyAsPossible, [] (const PassManagerBuilder&,
								       legacy::PassManagerBase& PM) {
    PM.add(new SimplePass());
  });

  RegisterPass<SimplePass> Y("SimplePass", "Simple Pass");
}
