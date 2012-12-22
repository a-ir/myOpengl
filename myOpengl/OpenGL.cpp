#include<iostream>
#include "RenderingALitSphere.h"
#include "DemonstratingBlendEquationModes.h"
#include "BlendingExampleAlpha.h"
#include "ThreeDimensionalBlending.h"
#include "AntialiasedLines.h"
#include "FiveFoggedSpheres.h"

enum Sample_Num{
	RenderingALitSphere_NO = 5,
	DemonstratingBlendEquationModes_NO = 6,
	BlendingExampleAlpha_NO = 7,
	ThreeDimensionalBlending_NO = 8,
	AntialiasedLines_NO = 9,
	FiveFoggedSpheres_NO = 10,
};

int main(int argc, char *argv[])
{
	int no;
	std::cin>>no;
	switch (no)
	{
	case RenderingALitSphere_NO:
		{
			RenderingALitSphere* objRAS = new RenderingALitSphere();
			objRAS->startup(argc,argv);
			break;
		}
	case DemonstratingBlendEquationModes_NO:
		{
			DemonstratingBlendEquationModes* objDBEM = new DemonstratingBlendEquationModes();
			objDBEM->startup(argc,argv);
			break;
		}
	case BlendingExampleAlpha_NO:
		{
			BlendingExampleAlpha* objBEA = new BlendingExampleAlpha();
			objBEA->startup(argc, argv);
			break;
		}
	case ThreeDimensionalBlending_NO:
		{
			ThreeDimensionalBlending* objTDB = new ThreeDimensionalBlending();
			objTDB->startup(argc,argv);
			break;
		}
	case AntialiasedLines_NO:
		{
			AntialiasedLines* objAL = new AntialiasedLines();
			objAL->startup(argc,argv);
			break;
		}
	case FiveFoggedSpheres_NO:
		{
			FiveFoggedSpheres* objFFS = new FiveFoggedSpheres();
			objFFS->startup(argc,argv);
			break;
		}
	}
	return 0; 
}