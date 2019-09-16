#include <apf.h>
#include <apfMesh2.h>
#include <gmi_mesh.h>
#include <gmi_sim.h>
#include <apfMDS.h>
#include <apfShape.h>
#include <PCU.h>
#include <SimUtil.h>
#include <MeshSim.h>
#include <cassert>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <iostream>
#include "lionPrint.h"
#include <parma.h>
#include "spr.h"
#include <apfConvert.h>

//Modify the CMakeList.txt to ensure correct file name etc
//remove build folder for a new build
//source setup.sh to do cmake
//build with ./build.sh destroyField
//run with mpirun -n 4 ./build/writeVTK 40x20x5umSi.dmg restart_0.05_.smb restart_0.05_updated


// main surface update function
int main(int argc, char** argv){
  assert(argc==4);
  const char* modelFile = argv[1];
  const char* meshFile = argv[2];
  const char* outFile = argv[3];
  MPI_Init(&argc,&argv);
  PCU_Comm_Init();
  MS_init();
  Sim_readLicenseFile(0);
  gmi_sim_start();
  gmi_register_mesh();
  gmi_register_sim();
  lion_set_verbosity(1);
  gmi_model* model = gmi_load(modelFile);
  apf::Mesh2* mesh = apf::loadMdsMesh(model,meshFile);
  
  int fieldsize = mesh -> countFields();
  while (fieldsize>1){
  		//std::cout<<"first field is " << apf::getName(mesh->getField(0) ) <<"\n";
  	    if( (mesh->getField(0)) == (mesh -> findField("Psi1")) ){
     	//std::cout<<"Psi1 not destroyed, next destroyed\n";
       	apf::destroyField( mesh->getField(1) );

     	//fieldsize -= 1;          
    	}
    	else{
        	//std::cout<<count<<"th field to be destroyed\n"; 
        	//with name "<<apf::getName(mesh->getField(count))<<", remaining " << mesh->countFields()<<"\n";    	
        	apf::destroyField( mesh->getField(0) );
        }
      fieldsize = mesh -> countFields();
  }
  std::cout<<"finally " << mesh -> countFields() << " fields "<<apf::getName(mesh->getField((mesh -> countFields())-1)) <<" kept\n";

    apf::writeVtkFiles(outFile,mesh);  
  //mesh->writeNative("restart_50_processed.smb");
}

  /*
  apf::Field *f = mesh->findField("Solution");
  if (f==NULL){
    std::cout<<"Solution field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Solution field destroyed\n";
  
  f = mesh->findField("temp_old");
  if (f==NULL){
    std::cout<<"temp_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"temp_old field destroyed\n";
  PCU_Barrier();
  //apf::writeASCIIVtkFiles(outFile,mesh);


  f = mesh->findField("Temperature_old");
  if (f==NULL){
    std::cout<<"temp_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Temperature_old field destroyed\n";

    f = mesh->findField("Temperature");
  if (f==NULL){
    std::cout<<"temp_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Temperature field destroyed\n";

    f = mesh->findField("Depth");
  if (f==NULL){
    std::cout<<"Depth field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Depth field destroyed\n";

    f = mesh->findField("Depth_old");
  if (f==NULL){
    std::cout<<"Depth_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Depth_old field destroyed\n";  

    f = mesh->findField("residual");
  if (f==NULL){
    std::cout<<"residual field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"residual field destroyed\n";

    f = mesh->findField("Phi1");
  if (f==NULL){
    std::cout<<"Phi1 field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Phi1 field destroyed\n";

      f = mesh->findField("Phi1_old");
  if (f==NULL){
    std::cout<<"Phi1_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Phi1_old field destroyed\n";

    f = mesh->findField("Phi2");
  if (f==NULL){
    std::cout<<"Phi2 field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Phi2 field destroyed\n";

      f = mesh->findField("Phi2_old");
  if (f==NULL){
    std::cout<<"Phi2_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Phi2_old field destroyed\n"; 

    f = mesh->findField("Psi2");
  if (f==NULL){
    std::cout<<"Psi2 field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Psi2 field destroyed\n";

      f = mesh->findField("Psi2_old");
  if (f==NULL){
    std::cout<<"Psi2_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Psi2_old field destroyed\n";  

        f = mesh->findField("Psi1_old");
  if (f==NULL){
    std::cout<<"Psi1_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Psi1_old field destroyed\n";  

    f = mesh->findField("Laser Source");
  if (f==NULL){
    std::cout<<"Laser Source field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Laser Source field destroyed\n";

      f = mesh->findField("Laser Source_old");
  if (f==NULL){
    std::cout<<"Laser Source_old field not found!\n";
  }  
  apf::destroyField(f);
  std::cout<<"Laser Source_old field destroyed\n";  

      //destroy all fields

      int fieldsize = mesh->countFields();
      std::cout<<"After destroy, "<<fieldsize<<" fields exists\n";
	*/


//***************************************************************************


