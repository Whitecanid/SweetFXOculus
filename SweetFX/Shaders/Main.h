  /*-------------------------.   
  | :: Defining constants :: |
  '-------------------------*/

//These values are normally defined by the injector dlls, but not when analyzed by GPU Shaderanalyzer
//I need to ensure they always have a value to be able to compile them whenever I'm not using the injector.
#ifdef SMAA_PIXEL_SIZE
  #ifndef BUFFER_RCP_WIDTH
    #define BUFFER_RCP_WIDTH SMAA_PIXEL_SIZE.x
    #define BUFFER_RCP_HEIGHT SMAA_PIXEL_SIZE.y
    #define BUFFER_WIDTH (1.0 / SMAA_PIXEL_SIZE.x)
    #define BUFFER_HEIGHT (1.0 / SMAA_PIXEL_SIZE.y)
  #endif
#endif

#ifndef BUFFER_RCP_WIDTH
  #define BUFFER_RCP_WIDTH (1.0 / 1680)
  #define BUFFER_RCP_HEIGHT (1.0 / 1050)
  #define BUFFER_WIDTH 1680
  #define BUFFER_HEIGHT 1050
#endif

#define screen_size float2(BUFFER_WIDTH,BUFFER_HEIGHT)

#define px BUFFER_RCP_WIDTH
#define py BUFFER_RCP_HEIGHT

#define pixel float2(px,py)

// -- Define DirectX9 FXAA specific aliases --
#if FXAA_HLSL_3 == 1
  #define myTex2D(s,p) tex2D(s,p)
  
  #define s0 frameSampler
  #define s1 frameSampler
#endif

// -- Define DirectX10/11 specific aliases --
#if FXAA_HLSL_4 == 1 || FXAA_HLSL_5 == 1
  #define myTex2D(s,p) s.SampleLevel(LinearSampler, p, 0)
  
  #define s0 frameTex2D
  #define s1 frameTex2D
#endif

// -- Define DirectX9 specific aliases --
#if SMAA_HLSL_3 == 1
  #define myTex2D(s,p) tex2D(s,p)
  
  #define s0 colorTexG
  #define s1 colorTexG //TODO make a nearest sampler if needed
#endif

// -- Define DirectX10/11 specific aliases --
#if SMAA_HLSL_4 == 1 || SMAA_HLSL_4_1 == 1
  #define myTex2D(s,p) s.SampleLevel(LinearSampler, p, 0)

  #define s0 colorTexGamma
  #define s1 colorTexGamma //TODO make a nearest sampler if needed
#endif


  /*------------------------------.   
  | :: Include enabled shaders :: |
  '------------------------------*/
  
#if (USE_CARTOON == 1)
  #include "Cartoon.h"
#endif  

#if (USE_ADVANCED_CRT == 1)
  #include "AdvancedCRT.h"
#endif

#if (USE_BLOOM == 1)
  #include "Bloom.h"
#endif

#if (USE_HDR == 1)
  #include "HDR.h"
#endif

#if (USE_LUMASHARPEN == 1)
  #include "LumaSharpen.h"
#endif

#if (USE_TECHNICOLOR == 1)
  #include "Technicolor.h"
#endif

#if (USE_DPX == 1)
  #include "DPX.h"
#endif

#if (USE_MONOCHROME == 1)
  #include "Monochrome.h"
#endif

#if (USE_LIFTGAMMAGAIN == 1)
  #include "LiftGammaGain.h"
#endif

#if (USE_TONEMAP == 1)
  #include "Tonemap.h"
#endif

#if (USE_SEPIA == 1)
  #include "Sepia.h"
#endif

#if (USE_VIBRANCE == 1)
  #include "Vibrance.h"
#endif

#if (USE_CURVES == 1)
  #include "Curves.h"
#endif

#if (USE_VIGNETTE == 1)
  #include "Vignette.h"
#endif

#if (USE_DITHER == 1)
  #include "Dither.h"
#endif

#if (USE_BORDER == 1)
  #include "Border.h"
#endif

#if (USE_SPLITSCREEN == 1)
  #include "Splitscreen.h"
#endif

  /*-------------------------------.   
  | :: Xbox360 Gamma correction :: |
  '-------------------------------*/

/*
  I suspect that some games that ported to PC are such terrible ports that the developers forgot (or didn't bother)
  to do correct gamma correction for PC but just copied the Xbox360 code.
  
  If that is the case then I can probably correct for it, but I need to find some terrible ports and check for this first.
  Until then this code is not used.
*/

//float XenonGammaToLinear(float val)
//{
//   float ret;
//   saturate(val);
//   if (val < 0.25f)
//      ret = 0.25f * val;
//   else if (val < 0.375f)
//      ret = (1.0f/16.0f) + 0.5f*(val-0.25f);
//   else if (val < 0.75f)
//      ret = 0.125f + 1.0f*(val-0.375f);
//   else
//      ret = 0.5f + 2.0f*(val-0.75f);
//   return ret;
//}
//
//float LinearToXenonGamma(float val)
//{
//   float ret;
//   saturate(val);
//   if (val < (1.0f/16.0f))
//      ret = 4.0f * val;
//   else if (val < (1.0f/8.0f))
//      ret = (1.0f/4.0f) + 2.0f*(val-(1.0f/16.0f));
//   else if (val < 0.5f)
//      ret = 0.375f + 1.0f*(val-0.125f);
//   else
//      ret = 0.75f + 0.5f*(val-0.50f);
//   return ret;
//}

  /*--------------------.   
  | :: Effect passes :: |
  '--------------------*/
//1.0f, 0.22f, 0.24f 0
//for k0, k1, k2, k3
//WHITECANID_DISTO_0 = k0
//WHITECANID_DISTO_1 = 

#define WHITECANID_DISTO_0 1.0
#define WHITECANID_DISTO_1 0.22
#define WHITECANID_DISTO_2 0.24
#define WHITECANID_DISTO_3 0

//HmdWarpParam = {x=1.0000000 y=0.22000000 z=0.23999999 0.0}
//ChromAbParam = {x=0.99599999 y=-0.0040000002 z=1.0140001 0.0}

//#define WHITECANID_CHROMAB_RED_0 0.99599999
//#define WHITECANID_CHROMAB_RED_1 -0.0040000002
//#define WHITECANID_CHROMAB_BLUE_0 1.0140001
//#define WHITECANID_CHROMAB_BLUE_1 0.0


#define WHITECANID_CHROMAB_RED_0 0.995
#define WHITECANID_CHROMAB_RED_1 -0.000
#define WHITECANID_CHROMAB_BLUE_0 1.0080
#define WHITECANID_CHROMAB_BLUE_1 0.0


#define WHITECANID_PRECORRECT_X 2
//1.25 = 800/(1280*0.5) oculus screen aspect ratio?
#define WHITECANID_PRECORRECT_Y 1.25
#define WHITECANID_POSTCORRECT_X 0.5
#define WHITECANID_POSTCORRECT_Y 0.8

#define WHITECANID_ELITE_ZOOMFACTOR_INVERT 0.65
#define WHITECANID_ELITE_STRETCHING_FACTOR_X 1
#define WHITECANID_ELITE_STRETCHING_FACTOR_Y 2


#define WHITECANID_OCULUSLENSOFFSET_X 0.05
#define WHITECANID_OCULUSLENSOFFSET_Y 0.0

#define WHITECANID_PHONEOFFSET_X 0.002
#define WHITECANID_PHONEOFFSET_Y -0.001

float2 WCClampL(float2 coor){
	if(coor.x<0) coor.x=0;
	if(coor.x>0.5) coor.x=0.5;
	if(coor.y<0) coor.y=0;
	if(coor.y>1) coor.y=1;
	return coor;
}

float2 WCClampR(float2 coor){
	if(coor.x<0.5) coor.x=0.5;
	if(coor.x>1) coor.x=1;
	if(coor.y<0) coor.y=0;
	if(coor.y>1) coor.y=1;
	return coor;
}

float2 WCCorrectAspectRatio(float2 coor){
	//x is cut in half due to screen splitting.
	//thus y must be compressed too, according to that same ratio
	float diffY = coor.y - 0.5;
	float y = 0.5 + diffY*2.0;
	//if(y<0) y=0; if(y>1)y=1;
	return float2(coor.x,y);
}

float WHITECANID_POLY(float rr){
	return (WHITECANID_DISTO_0 + (rr *(WHITECANID_DISTO_1 + (rr * (WHITECANID_DISTO_2 + (rr * WHITECANID_DISTO_3))))));
}

float WCBarrelDistortOp_RED(float2 offset){
	float rr = offset.x*offset.x + offset.y*offset.y;
	return WHITECANID_POLY(rr) * (WHITECANID_CHROMAB_RED_0 + WHITECANID_CHROMAB_RED_1*rr);			
}

float WCBarrelDistortOp_GREEN(float2 offset){
	float rr = offset.x*offset.x + offset.y*offset.y;
	return WHITECANID_POLY(rr);			
}

float WCBarrelDistortOp_BLUE(float2 offset){
	float rr = offset.x*offset.x + offset.y*offset.y;
	return WHITECANID_POLY(rr) * (WHITECANID_CHROMAB_BLUE_0 + WHITECANID_CHROMAB_BLUE_1*rr);			
}

//reference function for barrel distort
float WCBarrelDistortOp(float2 offset){
	float rr = offset.x*offset.x + offset.y*offset.y;
	return WHITECANID_DISTO_0 +
		(rr *(WHITECANID_DISTO_1 + 
		 (rr * (WHITECANID_DISTO_2 + 
			(rr * WHITECANID_DISTO_3)))));
}



float2 WCPreTranslate(float2 coor, float2 offset){
	return float2(coor.x+offset.x, coor.y+offset.y);
}

float2 WCPreBarrel(float2 offset){
	offset.x*=WHITECANID_PRECORRECT_X;
	offset.y*=WHITECANID_PRECORRECT_Y;
	return offset;
}

float2 WCPostBarrel(float2 offset){
	offset.x*= (WHITECANID_POSTCORRECT_X * WHITECANID_ELITE_STRETCHING_FACTOR_X * WHITECANID_ELITE_ZOOMFACTOR_INVERT);
	offset.y*= (WHITECANID_POSTCORRECT_Y * WHITECANID_ELITE_STRETCHING_FACTOR_Y * WHITECANID_ELITE_ZOOMFACTOR_INVERT);
	return offset;
}

//reference function for barrel distort
float2 WCBarrelDistort(float2 coor, float2 center)
{
	float2 tmp = WCPreBarrel(float2(coor.x-center.x, coor.y-center.y));
	float distoSq =  WCBarrelDistortOp(tmp);
	float2 tmp2 = WCPostBarrel(float2(tmp.x*distoSq, tmp.y*distoSq));
	return float2(center.x + tmp2.x, center.y + tmp2.y);
}

//RED
float2 WCBarrelDistort_RED(float2 coor, float2 center)
{
	float2 tmp = WCPreBarrel(float2(coor.x-center.x, coor.y-center.y));
	float distoSq =  WCBarrelDistortOp_RED(tmp);
	float2 tmp2 = WCPostBarrel(float2(tmp.x*distoSq, tmp.y*distoSq));
	return float2(center.x + tmp2.x, center.y + tmp2.y);
}

//GREEN
float2 WCBarrelDistort_GREEN(float2 coor, float2 center)
{
	float2 tmp = WCPreBarrel(float2(coor.x-center.x, coor.y-center.y));
	float distoSq =  WCBarrelDistortOp_GREEN(tmp);
	float2 tmp2 = WCPostBarrel(float2(tmp.x*distoSq, tmp.y*distoSq));
	return float2(center.x + tmp2.x, center.y + tmp2.y);
}

//BLUE
float2 WCBarrelDistort_BLUE(float2 coor, float2 center)
{
	float2 tmp = WCPreBarrel(float2(coor.x-center.x, coor.y-center.y));
	float distoSq =  WCBarrelDistortOp_BLUE(tmp);
	float2 tmp2 = WCPostBarrel(float2(tmp.x*distoSq, tmp.y*distoSq));
	return float2(center.x + tmp2.x, center.y + tmp2.y);
}
  
float4 WhiteCanidPass_OLD( float4 colorInput, float2 tex )
{
	// -- Vertical 50/50 split --
	//return colorInput;
	//return (tex.x>0.2 && tex.x<0.3 && tex.y>0.5 && tex.y<0.7)?float4(0.4,0.9,0.3,1.0) :  myTex2D(s0, tex);
	// return (tex.x < 0.5) ? myTex2D(s0, tex) : colorInput;
	//return (tex.x>0.2 && tex.x<0.3 && tex.y>0.5 && tex.y<0.7)? myTex2D(s0,float2(0.2+0.8-tex.x*0.5,0.3+tex.y*0.5)) :  myTex2D(s0, tex);
	 
	//float2 centerL(0.25,0.5);
	
	if(tex.x>=0.5){ //right screen
		float2 centerR = float2(0.75,0.5);
		float2 translR = float2(WHITECANID_OCULUSLENSOFFSET_X-WHITECANID_PHONEOFFSET_X, -WHITECANID_OCULUSLENSOFFSET_Y-WHITECANID_PHONEOFFSET_Y);
		return myTex2D(s0, /*WCClampR*/(WCBarrelDistort(WCPreTranslate(tex,translR), centerR)));
		//return myTex2D(s0, WCClampR(WCCorrectAspectRatio(tex)));
		//return myTex2D(s0, centerR);
		//return myTex2D(s0, float2(1.0-tex.x, tex.y));
	}
	else{ //left screen
	//return myTex2D(s0,tex);
		float2 centerL = float2(0.25,0.5);
		float2 translL = float2(-WHITECANID_OCULUSLENSOFFSET_X-WHITECANID_PHONEOFFSET_X, -WHITECANID_OCULUSLENSOFFSET_Y-WHITECANID_PHONEOFFSET_Y);
		return myTex2D(s0, /*WCClampL*/(WCBarrelDistort(WCPreTranslate(tex,translL), centerL)));
		
	}
}
 
 float4 WCBloomPass( float4 ColorInput2,float2 Tex  )
{
	float3 BlurColor2 = 0;
	float3 Blurtemp = 0;
	float MaxDistance = sqrt(8*BloomWidth);
	float CurDistance = 0;
	
	//float Samplecount = 0;
	float Samplecount = 25.0;
	
	float2 blurtempvalue = Tex * pixel * BloomWidth;
	
	//float distancetemp = 1.0 - ((MaxDistance - CurDistance) / MaxDistance);
	
	float2 BloomSample = float2(2.5,-2.5);
	float2 BloomSampleValue;// = BloomSample;
	
	for(BloomSample.x = (2.5); BloomSample.x > -2.0; BloomSample.x = BloomSample.x - 1.0) // runs 5 times
	{
        BloomSampleValue.x = BloomSample.x * blurtempvalue.x;
        float2 distancetemp = BloomSample.x * BloomSample.x * BloomWidth;
        
		for(BloomSample.y = (- 2.5); BloomSample.y < 2.0; BloomSample.y = BloomSample.y + 1.0) // runs 5 ( * 5) times
		{
            distancetemp.y = BloomSample.y * BloomSample.y;
			//CurDistance = sqrt(dot(BloomSample,BloomSample)*BloomWidth); //dot() attempt - same result , same speed. //move x part up ?
			CurDistance = sqrt( (distancetemp.y * BloomWidth) + distancetemp.x); //dot() attempt - same result , same speed. //move x part up ?
			
			//Blurtemp.rgb = myTex2D(s0, float2(Tex + (BloomSample*blurtempvalue))); //same result - same speed.
			BloomSampleValue.y = BloomSample.y * blurtempvalue.y;
			Blurtemp.rgb = myTex2D(s0, float2(Tex + BloomSampleValue)).rgb; //same result - same speed.
			
			//BlurColor2.rgb += lerp(Blurtemp.rgb,ColorInput2.rgb, 1 - ((MaxDistance - CurDistance)/MaxDistance)); //convert float4 to float3 and check if it's possible to use a MAD
			BlurColor2.rgb += lerp(Blurtemp.rgb,ColorInput2.rgb, 1.0 - ((MaxDistance - CurDistance) / MaxDistance)); //convert float4 to float3 and check if it's possible to use a MAD
			
			//Samplecount = Samplecount + 1; //take out of loop and replace with constant if it helps (check with compiler)
		}
	}
	BlurColor2.rgb = (BlurColor2.rgb / (Samplecount - (BloomPower - BloomThreshold*5))); //check if using MAD
	float Bloomamount = (dot(ColorInput2.rgb,float3(0.299f, 0.587f, 0.114f))) ; //try BT 709
	float3 BlurColor = BlurColor2.rgb * (BloomPower + 4.0); //check if calculated offline and combine with line 24 (the blurcolor2 calculation)

	ColorInput2.rgb = lerp(ColorInput2.rgb,BlurColor.rgb, Bloomamount);	

	return saturate(ColorInput2);
}


float4 WCHDRPass( float4 colorInput, float2 Tex )
{
	float3 c_center = myTex2D(s0, Tex).rgb; //reuse SMAA center sample or lumasharpen center sample?
	//float3 c_center = colorInput.rgb; //or just the input?
	
	//float3 bloom_sum1 = float3(0.0, 0.0, 0.0); //don't initialize to 0 - use the first tex2D to do that
	//float3 bloom_sum2 = float3(0.0, 0.0, 0.0); //don't initialize to 0 - use the first tex2D to do that
	//Tex += float2(0, 0); // +0 ? .. oh riiiight - that will surely do something useful
	
	float radius1 = 0.793;
	float3 bloom_sum1 = myTex2D(s0, Tex + float2(1.5, -1.5) * radius1).rgb;
	bloom_sum1 += myTex2D(s0, Tex + float2(-1.5, -1.5) * radius1).rgb; //rearrange sample order to minimize ALU and maximize cache usage
	bloom_sum1 += myTex2D(s0, Tex + float2(1.5, 1.5) * radius1).rgb;
	bloom_sum1 += myTex2D(s0, Tex + float2(-1.5, 1.5) * radius1).rgb;
	
	bloom_sum1 += myTex2D(s0, Tex + float2(0, -2.5) * radius1).rgb;
	bloom_sum1 += myTex2D(s0, Tex + float2(0, 2.5) * radius1).rgb;
	bloom_sum1 += myTex2D(s0, Tex + float2(-2.5, 0) * radius1).rgb;
	bloom_sum1 += myTex2D(s0, Tex + float2(2.5, 0) * radius1).rgb;
	
	bloom_sum1 *= 0.005;
	
	float3 bloom_sum2 = myTex2D(s0, Tex + float2(1.5, -1.5) * radius2).rgb;
	bloom_sum2 += myTex2D(s0, Tex + float2(-1.5, -1.5) * radius2).rgb;
	bloom_sum2 += myTex2D(s0, Tex + float2(1.5, 1.5) * radius2).rgb;
	bloom_sum2 += myTex2D(s0, Tex + float2(-1.5, 1.5) * radius2).rgb;


	bloom_sum2 += myTex2D(s0, Tex + float2(0, -2.5) * radius2).rgb;	
	bloom_sum2 += myTex2D(s0, Tex + float2(0, 2.5) * radius2).rgb;
	bloom_sum2 += myTex2D(s0, Tex + float2(-2.5, 0) * radius2).rgb;
	bloom_sum2 += myTex2D(s0, Tex + float2(2.5, 0) * radius2).rgb;

	bloom_sum2 *= 0.010;
	
	float dist = radius2 - radius1;
	
	float3 HDR = (c_center + (bloom_sum2 - bloom_sum1)) * dist;
	float3 blend = HDR + colorInput.rgb;
	colorInput.rgb = HDR + pow(blend, HDRPower); // pow - don't use fractions for HDRpower
	
	return saturate(colorInput);
}


   /*-----------------------------------------------------------.
  /                      Developer settings                     /
  '-----------------------------------------------------------*/
#define CoefLuma float3(0.2126, 0.7152, 0.0722)      // BT.709 & sRBG luma coefficient (Monitors and HD Television)
//#define CoefLuma float3(0.299, 0.587, 0.114)       // BT.601 luma coefficient (SD Television)
//#define CoefLuma float3(1.0/3.0, 1.0/3.0, 1.0/3.0) // Equal weight coefficient

   /*-----------------------------------------------------------.
  /                          Main code                          /
  '-----------------------------------------------------------*/

float4 WCLumaSharpenPass(float4 inputcolor, float2 tex )
{
  // -- Get the original pixel --
  float3 ori = myTex2D(s0, tex).rgb;       // ori = original pixel

  // -- Combining the strength and luma multipliers --
  float3 sharp_strength_luma = (CoefLuma * sharp_strength); //I'll be combining even more multipliers with it later on

   /*-----------------------------------------------------------.
  /                       Sampling patterns                     /
  '-----------------------------------------------------------*/
  //   [ NW,   , NE ] Each texture lookup (except ori)
  //   [   ,ori,    ] samples 4 pixels
  //   [ SW,   , SE ]

  // -- Pattern 1 -- A (fast) 7 tap gaussian using only 2+1 texture fetches.
  #if pattern == 1

	// -- Gaussian filter --
	//   [ 1/9, 2/9,    ]     [ 1 , 2 ,   ]
	//   [ 2/9, 8/9, 2/9]  =  [ 2 , 8 , 2 ]
 	//   [    , 2/9, 1/9]     [   , 2 , 1 ]

    float3 blur_ori = myTex2D(s0, tex + (float2(px,py) / 3.0) * offset_bias).rgb;  // North West
    blur_ori += myTex2D(s0, tex + (float2(-px,-py) / 3.0) * offset_bias).rgb; // South East

    //blur_ori += myTex2D(s0, tex + float2(px,py) / 3.0 * offset_bias); // North East
    //blur_ori += myTex2D(s0, tex + float2(-px,-py) / 3.0 * offset_bias); // South West

    blur_ori /= 2;  //Divide by the number of texture fetches

    sharp_strength_luma *= 1.5; // Adjust strength to aproximate the strength of pattern 2

  #endif

  // -- Pattern 2 -- A 9 tap gaussian using 4+1 texture fetches.
  #if pattern == 2

	// -- Gaussian filter --
	//   [ .25, .50, .25]     [ 1 , 2 , 1 ]
	//   [ .50,   1, .50]  =  [ 2 , 4 , 2 ]
 	//   [ .25, .50, .25]     [ 1 , 2 , 1 ]


    float3 blur_ori = myTex2D(s0, tex + float2(px,-py) * 0.5 * offset_bias).rgb; // South East
    blur_ori += myTex2D(s0, tex + float2(-px,-py) * 0.5 * offset_bias).rgb;  // South West
    blur_ori += myTex2D(s0, tex + float2(px,py) * 0.5 * offset_bias).rgb; // North East
    blur_ori += myTex2D(s0, tex + float2(-px,py) * 0.5 * offset_bias).rgb; // North West

    blur_ori *= 0.25;  // ( /= 4) Divide by the number of texture fetches

  #endif

  // -- Pattern 3 -- An experimental 17 tap gaussian using 4+1 texture fetches.
  #if pattern == 3

	// -- Gaussian filter --
	//   [   , 4 , 6 ,   ,   ]
	//   [   ,16 ,24 ,16 , 4 ]
	//   [ 6 ,24 ,   ,24 , 6 ]
	//   [ 4 ,16 ,24 ,16 ,   ]
	//   [   ,   , 6 , 4 ,   ]

    float3 blur_ori = myTex2D(s0, tex + float2(0.4*px,-1.2*py)* offset_bias).rgb;  // South South East
    blur_ori += myTex2D(s0, tex + float2(-1.2*px,-0.4*py) * offset_bias).rgb; // West South West
    blur_ori += myTex2D(s0, tex + float2(1.2*px,0.4*py) * offset_bias).rgb; // East North East
    blur_ori += myTex2D(s0, tex + float2(-0.4*px,1.2*py) * offset_bias).rgb; // North North West

    blur_ori *= 0.25;  // ( /= 4) Divide by the number of texture fetches

    sharp_strength_luma *= 0.51;
  #endif

  // -- Pattern 4 -- A 9 tap high pass (pyramid filter) using 4+1 texture fetches.
  #if pattern == 4

	// -- Gaussian filter --
	//   [ .50, .50, .50]     [ 1 , 1 , 1 ]
	//   [ .50,    , .50]  =  [ 1 ,   , 1 ]
 	//   [ .50, .50, .50]     [ 1 , 1 , 1 ]

    float3 blur_ori = myTex2D(s0, tex + float2(0.5 * px,-py * offset_bias)).rgb;  // South South East
    blur_ori += myTex2D(s0, tex + float2(offset_bias * -px,0.5 * -py)).rgb; // West South West
    blur_ori += myTex2D(s0, tex + float2(offset_bias * px,0.5 * py)).rgb; // East North East
    blur_ori += myTex2D(s0, tex + float2(0.5 * -px,py * offset_bias)).rgb; // North North West

    //blur_ori += (2 * ori); // Probably not needed. Only serves to lessen the effect.

    blur_ori /= 4.0;  //Divide by the number of texture fetches

    sharp_strength_luma *= 0.666; // Adjust strength to aproximate the strength of pattern 2
  #endif

  // -- Pattern 8 -- A (slower) 9 tap gaussian using 9 texture fetches.
  #if pattern == 8

	// -- Gaussian filter --
	//   [ 1 , 2 , 1 ]
	//   [ 2 , 4 , 2 ]
 	//   [ 1 , 2 , 1 ]

    half3 blur_ori = myTex2D(s0, tex + float2(-px,py) * offset_bias).rgb; // North West
    blur_ori += myTex2D(s0, tex + float2(px,-py) * offset_bias).rgb;     // South East
    blur_ori += myTex2D(s0, tex + float2(-px,-py)  * offset_bias).rgb;  // South West
    blur_ori += myTex2D(s0, tex + float2(px,py) * offset_bias).rgb;    // North East

    half3 blur_ori2 = myTex2D(s0, tex + float2(0,py) * offset_bias).rgb; // North
    blur_ori2 += myTex2D(s0, tex + float2(0,-py) * offset_bias).rgb;    // South
    blur_ori2 += myTex2D(s0, tex + float2(-px,0) * offset_bias).rgb;   // West
    blur_ori2 += myTex2D(s0, tex + float2(px,0) * offset_bias).rgb;   // East
    blur_ori2 *= 2.0;

    blur_ori += blur_ori2;
    blur_ori += (ori * 4); // Probably not needed. Only serves to lessen the effect.

    // dot()s with gaussian strengths here?

    blur_ori /= 16.0;  //Divide by the number of texture fetches

    //sharp_strength_luma *= 0.75; // Adjust strength to aproximate the strength of pattern 2
  #endif

  // -- Pattern 9 -- A (slower) 9 tap high pass using 9 texture fetches.
  #if pattern == 9

	// -- Gaussian filter --
	//   [ 1 , 1 , 1 ]
	//   [ 1 , 1 , 1 ]
 	//   [ 1 , 1 , 1 ]

    float3 blur_ori = myTex2D(s0, tex + float2(-px,py) * offset_bias).rgb; // North West
    blur_ori += myTex2D(s0, tex + float2(px,-py) * offset_bias).rgb;     // South East
    blur_ori += myTex2D(s0, tex + float2(-px,-py)  * offset_bias).rgb;  // South West
    blur_ori += myTex2D(s0, tex + float2(px,py) * offset_bias).rgb;    // North East

    blur_ori += ori.rgb; // Probably not needed. Only serves to lessen the effect.

    blur_ori += myTex2D(s0, tex + float2(0,py) * offset_bias).rgb;    // North
    blur_ori += myTex2D(s0, tex + float2(0,-py) * offset_bias).rgb;  // South
    blur_ori += myTex2D(s0, tex + float2(-px,0) * offset_bias).rgb; // West
    blur_ori += myTex2D(s0, tex + float2(px,0) * offset_bias).rgb; // East

    blur_ori /= 9;  //Divide by the number of texture fetches

    //sharp_strength_luma *= (8.0/9.0); // Adjust strength to aproximate the strength of pattern 2
  #endif


   /*-----------------------------------------------------------.
  /                            Sharpen                          /
  '-----------------------------------------------------------*/

  // -- Calculate the sharpening --
  float3 sharp = ori - blur_ori;  //Subtracting the blurred image from the original image

  #if 0 //New experimental limiter .. not yet finished
    float sharp_luma = dot(sharp, sharp_strength_luma); //Calculate the luma
    sharp_luma = (abs(sharp_luma)*8.0) * exp(1.0-(abs(sharp_luma)*8.0)) * sign(sharp_luma) / 16.0; //I should probably move the strength modifier here

  #elif 0 //SweetFX 1.4 code
    // -- Adjust strength of the sharpening --
    float sharp_luma = dot(sharp, sharp_strength_luma); //Calculate the luma and adjust the strength

    // -- Clamping the maximum amount of sharpening to prevent halo artifacts --
    sharp_luma = clamp(sharp_luma, -sharp_clamp, sharp_clamp);  //TODO Try a curve function instead of a clamp
  
  #else //SweetFX 1.5.1 code
    // -- Adjust strength of the sharpening and clamp it--
    float4 sharp_strength_luma_clamp = float4(sharp_strength_luma * (0.5 / sharp_clamp),0.5); //Roll part of the clamp into the dot

    //sharp_luma = saturate((0.5 / sharp_clamp) * sharp_luma + 0.5); //scale up and clamp
    float sharp_luma = saturate(dot(float4(sharp,1.0), sharp_strength_luma_clamp)); //Calculate the luma, adjust the strength, scale up and clamp
    sharp_luma = (sharp_clamp * 2.0) * sharp_luma - sharp_clamp; //scale down
  #endif

  // -- Combining the values to get the final sharpened pixel	--
  //float4 done = ori + sharp_luma;    // Add the sharpening to the original.
  inputcolor.rgb = inputcolor.rgb + sharp_luma;    // Add the sharpening to the input color.

   /*-----------------------------------------------------------.
  /                     Returning the output                    /
  '-----------------------------------------------------------*/
  #if show_sharpen == 1
    //inputcolor.rgb = abs(sharp * 4.0);
    inputcolor.rgb = saturate(0.5 + (sharp_luma * 4)).rrr;
  #endif

  return saturate(inputcolor);

}

#define WHITECANID_FLAGS_ADVPROCESS_LEFT
#define WHITECANID_FLAGS_ADVPROCESS_RIGHT

#define WHITECANID_FLAGS_USEBLOOM
#define WHITECANID_FLAGS_USEHDR
#define WHITECANID_FLAGS_USELUMASHARPEN

#define WHITECANID_FLAGS_COLORCORRECTION
#define WHITECANID_CROP_VERTICAL_FACTOR 0.134
//#define WHITECANID_CROP_HORIZONTAL_FACTOR 0.1
#define WHITECANID_CROP_HORIZONTAL_FACTOR 0.0
float4 WhiteCanidPass( float4 colorInput, float2 tex )
{
	//cut processing time by not processing the edges of screen
	if(tex.x<WHITECANID_CROP_HORIZONTAL_FACTOR) return float4(0,0,0,0);
	if(tex.x>(1-WHITECANID_CROP_HORIZONTAL_FACTOR)) return float4(0,0,0,0);
	if(tex.y<WHITECANID_CROP_VERTICAL_FACTOR) return float4(0,0,0,0);
	if(tex.y>(1-WHITECANID_CROP_VERTICAL_FACTOR)) return float4(0,0,0,0);
	
	if(tex.x>=0.5){ //right screen
		float2 centerR = float2(0.75,0.5);
		float2 translR = float2(WHITECANID_OCULUSLENSOFFSET_X-WHITECANID_PHONEOFFSET_X, -WHITECANID_OCULUSLENSOFFSET_Y-WHITECANID_PHONEOFFSET_Y);
		float2 tmpTranslated = WCPreTranslate(tex,translR); 
		float2 redpt = WCBarrelDistort_RED(tmpTranslated, centerR);
		float2 greenpt = WCBarrelDistort_GREEN(tmpTranslated, centerR);
		float2 bluept = WCBarrelDistort_BLUE(tmpTranslated, centerR);
		
		float4 red =  myTex2D(s0, redpt);
		float4 green = myTex2D(s0, greenpt);
		float4 blue = myTex2D(s0, bluept);
#ifdef WHITECANID_FLAGS_ADVPROCESS_RIGHT
	#ifdef WHITECANID_FLAGS_USEBLOOM		
			red = WCBloomPass(red, redpt);
			green = WCBloomPass(green,greenpt);
			blue = WCBloomPass(blue,bluept);
	#endif		
	#ifdef WHITECANID_FLAGS_USEHDR
			red = WCHDRPass(red, redpt);
			green = WCHDRPass(green,greenpt);
			blue = WCHDRPass(blue,bluept);
	#endif

	#ifdef WHITECANID_FLAGS_USELUMASHARPEN
			red = WCLumaSharpenPass(red, redpt);
			green = WCLumaSharpenPass(green,greenpt);
			blue = WCLumaSharpenPass(blue,bluept);
	#endif
#endif
		return float4(red.x, green.y, blue.z, green.w);
	}
	else{ //left 
	//return myTex2D(s0,tex);
	
		float2 centerL = float2(0.25,0.5);
		float2 translL = float2(-WHITECANID_OCULUSLENSOFFSET_X-WHITECANID_PHONEOFFSET_X, -WHITECANID_OCULUSLENSOFFSET_Y-WHITECANID_PHONEOFFSET_Y);
		float2 tmpTranslated = WCPreTranslate(tex,translL); 
		float2 redpt = WCBarrelDistort_RED(tmpTranslated, centerL);
		float2 greenpt = WCBarrelDistort_GREEN(tmpTranslated, centerL);
		float2 bluept = WCBarrelDistort_BLUE(tmpTranslated, centerL);
		
		float4 red =  myTex2D(s0, redpt);
		float4 green = myTex2D(s0, greenpt);
		float4 blue = myTex2D(s0, bluept);
#ifdef WHITECANID_FLAGS_ADVPROCESS_LEFT
	#ifdef WHITECANID_FLAGS_USEBLOOM		
			red = WCBloomPass(red, redpt);
			green = WCBloomPass(green,greenpt);
			blue = WCBloomPass(blue,bluept);
	#endif		
	#ifdef WHITECANID_FLAGS_USEHDR
			red = WCHDRPass(red, redpt);
			green = WCHDRPass(green,greenpt);
			blue = WCHDRPass(blue,bluept);
	#endif

	#ifdef WHITECANID_FLAGS_USELUMASHARPEN
			red = WCLumaSharpenPass(red, redpt);
			green = WCLumaSharpenPass(green,greenpt);
			blue = WCLumaSharpenPass(blue,bluept);
	#endif
#endif
		return float4(red.x, green.y, blue.z, green.w);
		
	}
  
}

float4 WCVibrance( float4 colorInput )
{
  #ifndef Vibrance_RGB_balance //for backwards compatibility with setting presets for older version.
    #define Vibrance_RGB_balance float3(1.00, 1.00, 1.00)
  #endif
  
  #define Vibrance_coeff float3(Vibrance_RGB_balance * Vibrance)

	float4 color = colorInput; //original input color
  float3 lumCoeff = float3(0.212656, 0.715158, 0.072186);  //Values to calculate luma with

	float luma = dot(lumCoeff, color.rgb); //calculate luma (grey)

	float max_color = max(colorInput.r, max(colorInput.g,colorInput.b)); //Find the strongest color
	float min_color = min(colorInput.r, min(colorInput.g,colorInput.b)); //Find the weakest color

  float color_saturation = max_color - min_color; //The difference between the two is the saturation

  //color.rgb = lerp(luma, color.rgb, (1.0 + (Vibrance * (1.0 - color_saturation)))); //extrapolate between luma and original by 1 + (1-saturation) - simple

  //color.rgb = lerp(luma, color.rgb, (1.0 + (Vibrance * (1.0 - (sign(Vibrance) * color_saturation))))); //extrapolate between luma and original by 1 + (1-saturation) - current
  color.rgb = lerp(luma, color.rgb, (1.0 + (Vibrance_coeff * (1.0 - (sign(Vibrance_coeff) * color_saturation))))); //extrapolate between luma and original by 1 + (1-saturation) - current

  //color.rgb = lerp(luma, color.rgb, 1.0 + (1.0-pow(color_saturation, 1.0 - (1.0-Vibrance))) ); //pow version

	return color; //return the result
	//return color_saturation.xxxx; //Visualize the saturation
}


float4 WCCurvesPass( float4 colorInput )
{
  float3 lumCoeff = float3(0.2126, 0.7152, 0.0722);  //Values to calculate luma with
  float Curves_contrast_blend = Curves_contrast;
  float PI = acos(-1); //3.1415926589

   /*-----------------------------------------------------------.
  /               Separation of Luma and Chroma                 /
  '-----------------------------------------------------------*/

  // -- Calculate Luma and Chroma if needed --
  #if Curves_mode != 2

    //calculate luma (grey)
    float luma = dot(lumCoeff, colorInput.rgb);

    //calculate chroma
	  float3 chroma = colorInput.rgb - luma;
  #endif

  // -- Which value to put through the contrast formula? --
  // I name it x because makes it easier to copy-paste to Graphtoy or Wolfram Alpha or another graphing program
  #if Curves_mode == 2
	  float3 x = colorInput.rgb; //if the curve should be applied to both Luma and Chroma
	#elif Curves_mode == 1
	  float3 x = chroma; //if the curve should be applied to Chroma
	  x = x * 0.5 + 0.5; //adjust range of Chroma from -1 -> 1 to 0 -> 1
  #else // Curves_mode == 0
    float x = luma; //if the curve should be applied to Luma
  #endif

   /*-----------------------------------------------------------.
  /                     Contrast formulas                       /
  '-----------------------------------------------------------*/

  // -- Curve 1 --
  #if Curves_formula == 1
    x = sin(PI * 0.5 * x); // Sin - 721 amd fps, +vign 536 nv
    x *= x;
    
    //x = 0.5 - 0.5*cos(PI*x);
    //x = 0.5 * -sin(PI * -x + (PI*0.5)) + 0.5;
  #endif

  // -- Curve 2 --
  #if Curves_formula == 2
    x = x - 0.5;  
    x = ( x / (0.5 + abs(x)) ) + 0.5;
    
    //x = ( (x - 0.5) / (0.5 + abs(x-0.5)) ) + 0.5;
  #endif

  // -- Curve 3 --
  #if Curves_formula == 3
    //x = smoothstep(0.0,1.0,x); //smoothstep
    x = x*x*(3.0-2.0*x); //faster smoothstep alternative - 776 amd fps, +vign 536 nv
    //x = x - 2.0 * (x - 1.0) * x* (x- 0.5);  //2.0 is contrast. Range is 0.0 to 2.0
  #endif

  // -- Curve 4 --
  #if Curves_formula == 4
    x = (1.0524 * exp(6.0 * x) - 1.05248) / (20.0855 + exp(6.0 * x)); //exp formula
  #endif

  // -- Curve 5 --
  #if Curves_formula == 5
    //x = 0.5 * (x + 3.0 * x * x - 2.0 * x * x * x); //a simplified catmull-rom (0,0,1,1) - btw smoothstep can also be expressed as a simplified catmull-rom using (1,0,1,0)
    //x = (0.5 * x) + (1.5 -x) * x*x; //estrin form - faster version
    x = x * (x * (1.5-x) + 0.5); //horner form - fastest version

    Curves_contrast_blend = Curves_contrast * 2.0; //I multiply by two to give it a strength closer to the other curves.
  #endif

 	// -- Curve 6 --
  #if Curves_formula == 6
    x = x*x*x*(x*(x*6.0 - 15.0) + 10.0); //Perlins smootherstep
	#endif

	// -- Curve 7 --
  #if Curves_formula == 7
    //x = ((x-0.5) / ((0.5/(4.0/3.0)) + abs((x-0.5)*1.25))) + 0.5;
	x = x - 0.5;
	x = x / ((abs(x)*1.25) + 0.375 ) + 0.5;
	//x = ( (x-0.5) / ((abs(x-0.5)*1.25) + (0.5/(4.0/3.0))) ) + 0.5;
  #endif

  // -- Curve 8 --
  #if Curves_formula == 8
    x = (x * (x * (x * (x * (x * (x * (1.6 * x - 7.2) + 10.8) - 4.2) - 3.6) + 2.7) - 1.8) + 2.7) * x * x; //Techicolor Cinestyle - almost identical to curve 1
  #endif

  // -- Curve 9 --
  #if Curves_formula == 9
    x =  -0.5 * (x*2.0-1.0) * (abs(x*2.0-1.0)-2.0) + 0.5; //parabola
  #endif

  // -- Curve 10 --
  #if Curves_formula == 10 //Half-circles

    #if Curves_mode == 0
      float xstep = step(x,0.5);
	    float xstep_shift = (xstep - 0.5);
	    float shifted_x = x + xstep_shift;
    #else
      float3 xstep = step(x,0.5);
	    float3 xstep_shift = (xstep - 0.5);
	    float3 shifted_x = x + xstep_shift;
    #endif

	x = abs(xstep - sqrt(-shifted_x * shifted_x + shifted_x) ) - xstep_shift;

  //x = abs(step(x,0.5)-sqrt(-(x+step(x,0.5)-0.5)*(x+step(x,0.5)-0.5)+(x+step(x,0.5)-0.5)))-(step(x,0.5)-0.5); //single line version of the above
    
  //x = 0.5 + (sign(x-0.5)) * sqrt(0.25-(x-trunc(x*2))*(x-trunc(x*2))); //worse
  
  /* // if/else - even worse
  if (x-0.5)
  x = 0.5-sqrt(0.25-x*x);
  else
  x = 0.5+sqrt(0.25-(x-1)*(x-1));
	*/

  //x = (abs(step(0.5,x)-clamp( 1-sqrt(1-abs(step(0.5,x)- frac(x*2%1)) * abs(step(0.5,x)- frac(x*2%1))),0 ,1))+ step(0.5,x) )*0.5; //worst so far
	
	//TODO: Check if I could use an abs split instead of step. It might be more efficient
	
	Curves_contrast_blend = Curves_contrast * 0.5; //I divide by two to give it a strength closer to the other curves.
  #endif

  // -- Curve 11 --
  #if Curves_formula == 11 //Cubic catmull
    float a = 1.00; //control point 1
    float b = 0.00; //start point
    float c = 1.00; //endpoint
    float d = 0.20; //control point 2
    x = 0.5 * ((-a + 3*b -3*c + d)*x*x*x + (2*a -5*b + 4*c - d)*x*x + (-a+c)*x + 2*b); //A customizable cubic catmull-rom spline
  #endif

  // -- Curve 12 --
  #if Curves_formula == 12 //Cubic Bezier spline
    float a = 0.00; //start point
    float b = 0.00; //control point 1
    float c = 1.00; //control point 2
    float d = 1.00; //endpoint

    float r  = (1-x);
	float r2 = r*r;
	float r3 = r2 * r;
	float x2 = x*x;
	float x3 = x2*x;
	//x = dot(float4(a,b,c,d),float4(r3,3*r2*x,3*r*x2,x3));

	//x = a * r*r*r + r * (3 * b * r * x + 3 * c * x*x) + d * x*x*x;
	//x = a*(1-x)*(1-x)*(1-x) +(1-x) * (3*b * (1-x) * x + 3 * c * x*x) + d * x*x*x;
	x = a*(1-x)*(1-x)*(1-x) + 3*b*(1-x)*(1-x)*x + 3*c*(1-x)*x*x + d*x*x*x;
  #endif

  // -- Curve 13 --
  #if Curves_formula == 13 //Cubic Bezier spline - alternative implementation.
    float3 a = float3(0.00,0.00,0.00); //start point
    float3 b = float3(0.25,0.15,0.85); //control point 1
    float3 c = float3(0.75,0.85,0.15); //control point 2
    float3 d = float3(1.00,1.00,1.00); //endpoint

    float3 ab = lerp(a,b,x);           // point between a and b
    float3 bc = lerp(b,c,x);           // point between b and c
    float3 cd = lerp(c,d,x);           // point between c and d
    float3 abbc = lerp(ab,bc,x);       // point between ab and bc
    float3 bccd = lerp(bc,cd,x);       // point between bc and cd
    float3 dest = lerp(abbc,bccd,x);   // point on the bezier-curve
    x = dest;
  #endif

  // -- Curve 14 --
  #if Curves_formula == 14
    x = 1.0 / (1.0 + exp(-(x * 10.0 - 5.0))); //alternative exp formula
  #endif

   /*-----------------------------------------------------------.
  /                 Joining of Luma and Chroma                  /
  '-----------------------------------------------------------*/

  #if Curves_mode == 2 //Both Luma and Chroma
	float3 color = x;  //if the curve should be applied to both Luma and Chroma
	colorInput.rgb = lerp(colorInput.rgb, color, Curves_contrast_blend); //Blend by Curves_contrast

  #elif Curves_mode == 1 //Only Chroma
	x = x * 2.0 - 1.0; //adjust the Chroma range back to -1 -> 1
	float3 color = luma + x; //Luma + Chroma
	colorInput.rgb = lerp(colorInput.rgb, color, Curves_contrast_blend); //Blend by Curves_contrast

  #else // Curves_mode == 0 //Only Luma
    x = lerp(luma, x, Curves_contrast_blend); //Blend by Curves_contrast
    colorInput.rgb = x + chroma; //Luma + Chroma

  #endif

  //Return the result
  return colorInput;
}
float4 WCSepiaPass( float4 colorInput )
{
	float3 sepia = colorInput.rgb;
	
	// colorInput.rgbalculating amounts of input, grey and sepia colors to blend and combine
	float grey = dot(sepia, float3(0.2126, 0.7152, 0.0722));
	
	sepia *= ColorTone;
	
	float3 blend2 = (grey * GreyPower) + (colorInput.rgb / (GreyPower + 1));

	colorInput.rgb = lerp(blend2, sepia, SepiaPower);
	
	// returning the final color
	return colorInput;
}


float4 main(float2 tex, float4 FinalColor)
{

 // #if (Xbox360gamma == 1)
 //   FinalColor.r = LinearToXenonGamma(FinalColor.r); // Linear to Xbox360 Gamma space (R)
 //   FinalColor.g = LinearToXenonGamma(FinalColor.g); // Linear to Xbox360 Gamma space (G)
 //   FinalColor.b = LinearToXenonGamma(FinalColor.b); // Linear to Xbox360 Gamma space (B)
	//#endif

  /*--------------------.   
  | :: Effect passes :: |
  '--------------------*/
  //Main coordinate dependent transforms (for Carton Oculus - barrel warping, etc.) here
  FinalColor = WhiteCanidPass(FinalColor,tex);
  //all coordinate independent color filters applied after WhiteCanidPass
  #ifdef WHITECANID_FLAGS_COLORCORRECTION
	  FinalColor = WCVibrance(FinalColor); 
	  FinalColor = WCCurvesPass(FinalColor);
	  FinalColor = WCSepiaPass(FinalColor);
  #endif
  
  // Cartoon
  #if (USE_CARTOON == 1)
	FinalColor = CartoonPass(FinalColor,tex);
  #endif
  
  // Advanced CRT
  #if (USE_ADVANCED_CRT == 1)
	FinalColor = AdvancedCRTPass(FinalColor,tex);
  #endif
	
	// Bloom
  #if (USE_BLOOM == 1)
	FinalColor = BloomPass (FinalColor,tex);
  #endif
	
	// HDR
  #if (USE_HDR == 1)
	FinalColor = HDRPass (FinalColor,tex);
  #endif
	
  // LumaSharpen
  #if (USE_LUMASHARPEN == 1)
	FinalColor = LumaSharpenPass(FinalColor,tex);
  #endif
		
  // Technicolor
  #if (USE_TECHNICOLOR == 1)
	FinalColor = TechnicolorPass(FinalColor);
  #endif
	
  // DPX
  #if (USE_DPX == 1)
	FinalColor = DPXPass(FinalColor);
  #endif
  
  // Monochrome
  #if (USE_MONOCHROME == 1)
	FinalColor = MonochromePass(FinalColor);
  #endif
	
  // Lift Gamma Gain
  #if (USE_LIFTGAMMAGAIN == 1)
	FinalColor = LiftGammaGainPass(FinalColor);
  #endif
	
  // Tonemap
  #if (USE_TONEMAP == 1)
	FinalColor = TonemapPass(FinalColor);
  #endif
	
  // Vibrance
  #if (USE_VIBRANCE == 1)
	FinalColor = VibrancePass(FinalColor);
  #endif

  // Curves
  #if (USE_CURVES == 1)
	FinalColor = CurvesPass(FinalColor);
  #endif
		
  // Sepia
  #if (USE_SEPIA == 1)
    FinalColor = SepiaPass(FinalColor);
  #endif
	
  // Vignette
  #if (USE_VIGNETTE == 1)
	FinalColor = VignettePass(FinalColor,tex);
  #endif
	
  // Dither (should go near the end as it only dithers what went before it)
  #if (USE_DITHER == 1)
	FinalColor = DitherPass(FinalColor,tex);
  #endif
	
  // Border
  #if (USE_BORDER == 1)
    FinalColor = BorderPass(FinalColor,tex);
  #endif
	
  // Splitscreen
  #if (USE_SPLITSCREEN == 1)
	FinalColor = SplitscreenPass(FinalColor,tex);
  #endif
  
	

  // Return FinalColor
  FinalColor.a = 1.0; //Clear alpha channel to reduce filesize of screenshots that are converted to png and avoid problems when viewing the screenshots.
  return FinalColor;
}