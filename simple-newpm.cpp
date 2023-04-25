#include <llvm/Pass.h>
#include <llvm/Passes/PassPlugin.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/IR/PassManager.h>

using namespace llvm;

namespace {

  class SimplePass : public PassInfoMixin<SimplePass> {
  public:
    PreservedAnalyses run(Function& F, FunctionAnalysisManager& FAM) {
      errs() << F.getName() << "\n";
      return PreservedAnalyses::all();
    }
    
  };
  
}

PassPluginLibraryInfo llvmGetPassPluginInfo() {
  const auto callback = [] (PassBuilder& PB) {
    PB.registerPipelineStartEPCallback([&] (ModulePassManager& MPM, auto) {
      FunctionPassManager FPM;
      FPM.addPass(SimplePass());
      MPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPM)));
      return true;
    });
  };

  return {LLVM_PLUGIN_API_VERSION, "SimplePass", "v0.0", callback};
}
