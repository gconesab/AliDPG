AliGenerator *
GeneratorCustom(TString opt = "")
{
  AliGenCocktail *ctl = (AliGenCocktail*) GeneratorCocktail("Hijing_LMee002");

  // Background events: HIJING (only if non-embedded)
  TString simulation = gSystem->Getenv("CONFIG_SIMULATION");
  if(!simulation.Contains("Embed")){
    AliGenerator   *hij   = GeneratorHijing();
    ctl->AddGenerator(hij,  "Hijing", 1.);
  }

  ////////////////////////////////////////////
  //    Pythia cc->ee
  ////////////////////////////////////////////
  AliGenPythia* pythiaCC = new AliGenPythia(-1);
  pythiaCC->SetTitle("PYTHIA-HF-Cdiele");
  pythiaCC->SetMomentumRange(0, 999999.);
  pythiaCC->SetThetaRange(0., 180.);
  pythiaCC->SetPtRange(0,1000.);
  pythiaCC->SetProcess(kPyCharmppMNRwmi);
  pythiaCC->SetEnergyCMS(energyConfig);
  pythiaCC->SetForceDecay(kSemiElectronic);
  //    Tune                                                                
  //    320     Perugia 0 
  //    350     Perugia 2011
  pythiaCC->SetTune(350);
  pythiaCC->UseNewMultipleInteractionsScenario();
  //
  //    decays 
  pythiaCC->SetCutOnChild(2);
  pythiaCC->SetPdgCodeParticleforAcceptanceCut(11);
  pythiaCC->SetChildYRange(-1.2,1.2);
  pythiaCC->SetChildPtRange(0,10000.);
  pythiaCC->SetStackFillOpt(AliGenPythia::kHeavyFlavor);

  ////////////////////////////////////////////
  //    Pythia bb->ee
  ////////////////////////////////////////////
  AliGenPythia* pythiaBB = new AliGenPythia(-1);
  pythiaBB->SetTitle("PYTHIA-HF-Bdiele");
  pythiaBB->SetMomentumRange(0, 999999.);
  pythiaBB->SetThetaRange(0., 180.);
  pythiaBB->SetPtRange(0,1000.);
  pythiaBB->SetProcess(kPyBeautyppMNRwmi);
  pythiaBB->SetEnergyCMS(energyConfig);
  pythiaBB->SetForceDecay(kSemiElectronic);
  //    Tune                                                                
  //    320     Perugia 0 
  //    350     Perugia 2011
  pythiaBB->SetTune(350);
  pythiaBB->UseNewMultipleInteractionsScenario();
  //
  //    decays 
  pythiaBB->SetCutOnChild(2);
  pythiaBB->SetPdgCodeParticleforAcceptanceCut(11);
  pythiaBB->SetChildYRange(-1.2,1.2);
  pythiaBB->SetChildPtRange(0,10000.);
  pythiaBB->SetStackFillOpt(AliGenPythia::kHeavyFlavor);


  ////////////////////////////////////////////
  //    Pythia b,c->e
  ////////////////////////////////////////////
  AliGenPythia* pythiaB= new AliGenPythia(-1);
  pythiaB->SetTitle("PYTHIA-HF-Bele");
  pythiaB->SetMomentumRange(0, 999999.);
  pythiaB->SetThetaRange(0., 180.);
  pythiaB->SetPtRange(0,1000.);
  pythiaB->SetProcess(kPyBeautyppMNRwmi);
  pythiaB->SetEnergyCMS(energyConfig);
  //    Tune                                                                
  //    320     Perugia 0 
  //    350     Perugia 2011
  pythiaB->SetTune(350);
  pythiaB->UseNewMultipleInteractionsScenario();
  //
  //    decays 
  pythiaB->SetCutOnChild(1);
  pythiaB->SetPdgCodeParticleforAcceptanceCut(11);
  pythiaB->SetChildYRange(-1.2,1.2);
  pythiaB->SetChildPtRange(0,10000.);
  pythiaB->SetStackFillOpt(AliGenPythia::kHeavyFlavor);


  ////////////////////////////////////////////
  //  Create cocktail
  ////////////////////////////////////////////

  // HF part only
  
  // centrality dependent yield (only if requested) 
  TFormula *formula = new TFormula("Signals","19 * exp(-0.5 * x*x/5.12/5.12) + 1");
 
    Int_t flag = (Int_t)gRandom->Uniform(0,100);
    if(flag>=0 && flag<20){
      if(opt.Contains("CentDepHF")){
	Printf("Setup HIJING_LMee002: Use centrality dependent injected HF: pythiaCC");
	ctl->AddGenerator(pythiaCC,"Pythia CC",1.,formula);
      }
      else{
	Printf("Setup HIJING_LMee002: Use centrality independent injected HF: pythiaCC");
	ctl->AddGenerator(pythiaCC,"Pythia CC",1.);
      }
    }else if(flag>=20 && flag<40){ 
      if(opt.Contains("CentDepHF")){
	Printf("Setup HIJING_LMee002: Use centrality dependent injected HF: pythiaBB");
	ctl->AddGenerator(pythiaBB,"Pythia BB",1.,formula);
      }
      else{
	Printf("Setup HIJING_LMee002: Use centrality independent injected HF: pythiaBB");
	ctl->AddGenerator(pythiaBB,"Pythia BB",1.);
      }
    }else if(flag>=40 && flag<100){ 
      if(opt.Contains("CentDepHF")){
	Printf("Setup HIJING_LMee002: Use centrality dependent injected HF: pythiaB");
	ctl->AddGenerator(pythiaB,"Pythia B",1.,formula);
      }
      else{
	Printf("Setup HIJING_LMee002: Use centrality independent injected HF: pythiaB");
	ctl->AddGenerator(pythiaB,"Pythia B",1.);
      }
    }
    
  return ctl;
}
