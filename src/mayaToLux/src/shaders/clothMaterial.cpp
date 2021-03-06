#include "clothMaterial.h"

#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/MArrayDataHandle.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnLightDataAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MFnMessageAttribute.h>
#include <maya/MFnGenericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFloatVector.h>
#include <maya/MGlobal.h>
#include <maya/MDrawRegistry.h>

// IFF type ID
// Each node requires a unique identifier which is used by
// MFnDependencyNode::create() to identify which node to create, and by
// the Maya file format.
//
// For local testing of nodes you can use any identifier between
// 0x00000000 and 0x0007ffff, but for any node that you plan to use for
// more permanent purposes, you should get a universally unique id from
// Autodesk Support. You will be assigned a unique range that you
// can manage on your own.
//
MTypeId	cloth::id( 0x0011CF57 );


// the postConstructor() function is called immediately after the objects
// constructor. It is not safe to call MPxNode member functions from the
// constructor, instead they should be called here.
//
void cloth::postConstructor( )
{
    // setMPSafe indicates that this shader can be used for multiprocessor
    // rendering. For a shading node to be MP safe, it cannot access any
    // shared global data and should only use attributes in the datablock
    // to get input data and store output data.
    //
    setMPSafe( true );
}


// DESCRIPTION: attribute information
//
MObject  cloth::aTranslucenceCoeff;
MObject  cloth::aDiffuseReflectivity;
MObject  cloth::aInTransparency;
MObject  cloth::aColor;
MObject  cloth::aIncandescence;
MObject  cloth::aOutColor;
MObject  cloth::aOutTransparency;
MObject  cloth::aNormalCamera;
MObject  cloth::aNormalCameraX;
MObject  cloth::aNormalCameraY;
MObject  cloth::aNormalCameraZ;
MObject  cloth::aLightData;
MObject  cloth::aLightDirection;
MObject  cloth::aLightDirectionX;
MObject  cloth::aLightDirectionY;
MObject  cloth::aLightDirectionZ;
MObject  cloth::aLightIntensity;
MObject  cloth::aLightIntensityR;
MObject  cloth::aLightIntensityG;
MObject  cloth::aLightIntensityB;
MObject  cloth::aLightAmbient;
MObject  cloth::aLightDiffuse;
MObject  cloth::aLightSpecular;
MObject  cloth::aLightShadowFraction;
MObject  cloth::aPreShadowIntensity;
MObject  cloth::aLightBlindData;

//---------------------------- automatically created attributes start ------------------------------------
MObject cloth::compo_visible_indirect_material;
MObject cloth::weft_Kd;
MObject cloth::compo_override_alpha_value;
MObject cloth::warp_Ks;
MObject cloth::repeat_u;
MObject cloth::repeat_v;
MObject cloth::compo_visible_emission;
MObject cloth::weft_Ks;
MObject cloth::compo_visible_material;
MObject cloth::compo_override_alpha;
MObject cloth::bumpmap;
MObject cloth::compo_visible_indirect_emission;
MObject cloth::warp_Kd;
MObject cloth::presetname;
//---------------------------- automatically created attributes end ------------------------------------


// This node does not need to perform any special actions on creation or
// destruction
//

cloth::cloth() { }
cloth::~cloth() { }


// The creator() method allows Maya to instantiate instances of this node.
// It is called every time a new instance of the node is requested by
// either the createNode command or the MFnDependencyNode::create()
// method.
//
// In this case creator simply returns a new cloth object.
//

void* cloth::creator()
{
    return new cloth();
}


// The initialize method is called only once when the node is first
// registered with Maya. In this method you define the attributes of the
// node, what data comes in and goes out of the node that other nodes may
// want to connect to.
//

MStatus cloth::initialize()
{
	MFnNumericAttribute nAttr;
	MFnLightDataAttribute lAttr;
	MFnTypedAttribute tAttr;
	MFnGenericAttribute gAttr;
	MFnEnumAttribute eAttr;
	MFnMessageAttribute mAttr;

    MStatus status; // Status will be used to hold the MStatus value
                    // returned by each api function call. It is important
                    // to check the status returned by a call to aid in
                    // debugging. Failed API calls can result in subtle
                    // errors that can be difficult to track down, you may
                    // wish to use the CHECK_MSTATUS macro for any API
                    // call where you do not need to provide your own
                    // error handling.
                    //

//---------------------------- automatically created attributes start ------------------------------------
	compo_visible_indirect_material = nAttr.create("compo_visible_indirect_material", "compo_visible_indirect_material",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( compo_visible_indirect_material ));

	weft_Kd = nAttr.createColor("weft_Kd", "weft_Kd");
	nAttr.setDefault(0.5,0.5,0.5);
	CHECK_MSTATUS(addAttribute( weft_Kd ));

	compo_override_alpha_value = nAttr.create("compo_override_alpha_value", "compo_override_alpha_value",  MFnNumericData::kFloat, 0.0);
	CHECK_MSTATUS(addAttribute( compo_override_alpha_value ));

	warp_Ks = nAttr.createColor("warp_Ks", "warp_Ks");
	nAttr.setDefault(0.5,0.5,0.5);
	CHECK_MSTATUS(addAttribute( warp_Ks ));

	repeat_u = nAttr.create("repeat_u", "repeat_u",  MFnNumericData::kFloat, 100.0);
	CHECK_MSTATUS(addAttribute( repeat_u ));

	repeat_v = nAttr.create("repeat_v", "repeat_v",  MFnNumericData::kFloat, 100.0);
	CHECK_MSTATUS(addAttribute( repeat_v ));

	compo_visible_emission = nAttr.create("compo_visible_emission", "compo_visible_emission",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( compo_visible_emission ));

	weft_Ks = nAttr.createColor("weft_Ks", "weft_Ks");
	nAttr.setDefault(0.5,0.5,0.5);
	CHECK_MSTATUS(addAttribute( weft_Ks ));

	compo_visible_material = nAttr.create("compo_visible_material", "compo_visible_material",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( compo_visible_material ));

	compo_override_alpha = nAttr.create("compo_override_alpha", "compo_override_alpha",  MFnNumericData::kBoolean, false);
	CHECK_MSTATUS(addAttribute( compo_override_alpha ));

	bumpmap = nAttr.createColor("bumpmap", "bumpmap");
	nAttr.setDefault(0.0,0.0,0.0);
	CHECK_MSTATUS(addAttribute( bumpmap ));

	compo_visible_indirect_emission = nAttr.create("compo_visible_indirect_emission", "compo_visible_indirect_emission",  MFnNumericData::kBoolean, true);
	CHECK_MSTATUS(addAttribute( compo_visible_indirect_emission ));

	warp_Kd = nAttr.createColor("warp_Kd", "warp_Kd");
	nAttr.setDefault(0.5,0.5,0.5);
	CHECK_MSTATUS(addAttribute( warp_Kd ));

	presetname = eAttr.create("presetname", "presetname", 1, &status);
	status = eAttr.addField( "silk_charmeuse", 0 );
	status = eAttr.addField( "denim", 1 );
	status = eAttr.addField( "cotton_twill", 2 );
	status = eAttr.addField( "wool_gabardine", 3 );
	status = eAttr.addField( "polyester_lining_cloth", 4 );
	status = eAttr.addField( "silk_shantung", 5 );
	CHECK_MSTATUS(addAttribute( presetname ));

//---------------------------- automatically created attributes end ------------------------------------

    // Input Attributes
    //
    aTranslucenceCoeff = nAttr.create( "translucenceCoeff", "tc",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.0f ) );

    aDiffuseReflectivity = nAttr.create( "diffuseReflectivity", "drfl",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.8f ) );

    aColor = nAttr.createColor( "color", "c", &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.0f, 0.58824f, 0.644f ) );

    aIncandescence = nAttr.createColor( "incandescence", "ic", &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.0f, 0.0f, 0.0f ) );

    aInTransparency = nAttr.createColor( "transparency", "it", &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setKeyable( true ) );
    CHECK_MSTATUS( nAttr.setStorable( true ) );
    CHECK_MSTATUS( nAttr.setDefault( 0.0f, 0.0f, 0.0f ) );

    // Color Output
    //
    aOutColor = nAttr.createColor( "outColor", "oc", &status );
    CHECK_MSTATUS( status );

    CHECK_MSTATUS( nAttr.setHidden( false ) );
    CHECK_MSTATUS( nAttr.setReadable( true ) );
    CHECK_MSTATUS( nAttr.setWritable( false ) );

    aOutTransparency = nAttr.createColor( "outTransparency", "ot", &status );
    CHECK_MSTATUS( status );

    CHECK_MSTATUS( nAttr.setHidden( false ) );
    CHECK_MSTATUS( nAttr.setReadable( true ) );
    CHECK_MSTATUS( nAttr.setWritable( false ) );

    // Camera Normals
    //
    aNormalCameraX = nAttr.create( "normalCameraX", "nx",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aNormalCameraY = nAttr.create( "normalCameraY", "ny",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aNormalCameraZ = nAttr.create( "normalCameraZ", "nz",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aNormalCamera = nAttr.create( "normalCamera","n", aNormalCameraX,
            aNormalCameraY, aNormalCameraZ, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( nAttr.setStorable( false ) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f, 1.0f, 1.0f ) );
    CHECK_MSTATUS( nAttr.setHidden( true ) );


    // Light Direction
    //
    aLightDirectionX = nAttr.create( "lightDirectionX", "ldx",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightDirectionY = nAttr.create( "lightDirectionY", "ldy",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightDirectionZ = nAttr.create( "lightDirectionZ", "ldz",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightDirection = nAttr.create( "lightDirection", "ld",
            aLightDirectionX, aLightDirectionY, aLightDirectionZ,
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f, 1.0f, 1.0f ) );


    // Light Intensity
    //
    aLightIntensityR = nAttr.create( "lightIntensityR", "lir",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightIntensityG = nAttr.create( "lightIntensityG", "lig",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightIntensityB = nAttr.create( "lightIntensityB", "lib",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightIntensity = nAttr.create( "lightIntensity", "li",
            aLightIntensityR, aLightIntensityG, aLightIntensityB,
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f, 1.0f, 1.0f ) );


    // Light
    //
    aLightAmbient = nAttr.create( "lightAmbient", "la",
            MFnNumericData::kBoolean, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( true ) );

    aLightDiffuse = nAttr.create( "lightDiffuse", "ldf",
            MFnNumericData::kBoolean, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( true ) );

    aLightSpecular = nAttr.create( "lightSpecular", "ls",
            MFnNumericData::kBoolean, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( false ) );

    aLightShadowFraction = nAttr.create( "lightShadowFraction", "lsf",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aPreShadowIntensity = nAttr.create( "preShadowIntensity", "psi",
            MFnNumericData::kFloat, 0, &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );
    CHECK_MSTATUS( nAttr.setDefault( 1.0f ) );

    aLightBlindData = nAttr.createAddr( "lightBlindData", "lbld",
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS ( nAttr.setStorable(false) );
    CHECK_MSTATUS ( nAttr.setHidden(true) );
    CHECK_MSTATUS ( nAttr.setReadable(true) );
    CHECK_MSTATUS ( nAttr.setWritable(false) );

    aLightData = lAttr.create( "lightDataArray", "ltd", aLightDirection,
            aLightIntensity, aLightAmbient, aLightDiffuse, aLightSpecular,
            aLightShadowFraction, aPreShadowIntensity, aLightBlindData,
            &status );
    CHECK_MSTATUS( status );
    CHECK_MSTATUS( lAttr.setArray( true ) );
    CHECK_MSTATUS( lAttr.setStorable( false ) );
    CHECK_MSTATUS( lAttr.setHidden( true ) );
    CHECK_MSTATUS( lAttr.setDefault( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            true, true, false, 1.0f, 1.0f, NULL ) );


    // Next we will add the attributes we have defined to the node
    //
    CHECK_MSTATUS( addAttribute( aTranslucenceCoeff ) );
    CHECK_MSTATUS( addAttribute( aDiffuseReflectivity ) );
    CHECK_MSTATUS( addAttribute( aColor ) );
    CHECK_MSTATUS( addAttribute( aIncandescence ) );
    CHECK_MSTATUS( addAttribute( aInTransparency ) );
    CHECK_MSTATUS( addAttribute( aOutColor ) );
    CHECK_MSTATUS( addAttribute( aOutTransparency ) );
    CHECK_MSTATUS( addAttribute( aNormalCamera ) );

    // Only add the parent of the compound
    CHECK_MSTATUS( addAttribute( aLightData ) );

    // The attributeAffects() method is used to indicate when the input
    // attribute affects the output attribute. This knowledge allows Maya
    // to optimize dependencies in the graph in more complex nodes where
    // there may be several inputs and outputs, but not all the inputs
    // affect all the outputs.
    //
    CHECK_MSTATUS( attributeAffects( aTranslucenceCoeff, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aDiffuseReflectivity, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aColor, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aInTransparency, aOutTransparency ) );
    CHECK_MSTATUS( attributeAffects( aInTransparency, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aIncandescence, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensityR, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensityB, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensityG, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightIntensity, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCameraX, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCameraY, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCameraZ, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aNormalCamera, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirectionX, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirectionY, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirectionZ, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDirection, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightAmbient, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightSpecular, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightDiffuse, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightShadowFraction, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aPreShadowIntensity, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightBlindData, aOutColor ) );
    CHECK_MSTATUS( attributeAffects( aLightData, aOutColor ) );

    return( MS::kSuccess );
}


// Compute takes two parameters: plug and data.
// - Plug is the the data value that needs to be recomputed
// - Data provides handles to all of the nodes attributes, only these
//   handles should be used when performing computations.
//
MStatus cloth::compute( const MPlug& plug, MDataBlock& block )
{
    // The plug parameter will allow us to determine which output attribute
    // needs to be calculated.
    //
	if( plug == aOutColor || plug == aOutTransparency || plug.parent() == aOutColor || plug.parent() == aOutTransparency  )
    {
        MStatus status;
        MFloatVector resultColor( 0.0, 0.0, 0.0 );

        // Get surface shading parameters from input block
        //
        MFloatVector& surfaceNormal = block.inputValue( aNormalCamera, &status ).asFloatVector();
        CHECK_MSTATUS( status );

        MFloatVector& surfaceColor = block.inputValue( aColor, &status ).asFloatVector();
        CHECK_MSTATUS( status );

        MFloatVector& incandescence = block.inputValue( aIncandescence,  &status ).asFloatVector();
        CHECK_MSTATUS( status );

        float diffuseReflectivity = block.inputValue( aDiffuseReflectivity, &status ).asFloat();
        CHECK_MSTATUS( status );

//      float translucenceCoeff = block.inputValue( aTranslucenceCoeff,
//              &status ).asFloat();
//      CHECK_MSTATUS( status );


        // Get light list
        //
        MArrayDataHandle lightData = block.inputArrayValue( aLightData, &status );
        CHECK_MSTATUS( status );

        int numLights = lightData.elementCount( &status );
        CHECK_MSTATUS( status );


        // Calculate the effect of the lights in the scene on the color
        //

        // Iterate through light list and get ambient/diffuse values
        //
        for( int count=1; count <= numLights; count++ )
        {
            // Get the current light out of the array
            //
            MDataHandle currentLight = lightData.inputValue( &status );
            CHECK_MSTATUS( status );


            // Get the intensity of that light
            //
            MFloatVector& lightIntensity = currentLight.child( aLightIntensity ).asFloatVector();


            // Find ambient component
            //
            if ( currentLight.child( aLightAmbient ).asBool() )
            {
                resultColor += lightIntensity;
            }


            // Find diffuse component
            //
            if ( currentLight.child( aLightDiffuse ).asBool() )
            {
                MFloatVector& lightDirection = currentLight.child( aLightDirection ).asFloatVector();
                float cosln = lightDirection * surfaceNormal;

               if ( cosln > 0.0f ) 
			   {
                    resultColor += lightIntensity * ( cosln * diffuseReflectivity );
               }
            }


            // Advance to the next light.
            //
            if ( count < numLights ) {
                status = lightData.next();
                CHECK_MSTATUS( status );
            }
        }


        // Factor incident light with surface color and add incandescence
        //
        resultColor[0] = resultColor[0] * surfaceColor[0] + incandescence[0];
        resultColor[1] = resultColor[1] * surfaceColor[1] + incandescence[1];
        resultColor[2] = resultColor[2] * surfaceColor[2] + incandescence[2];


        // Set ouput color attribute
        //
		if ( plug == aOutColor || plug.parent() == aOutColor )
        {
            // Get the handle to the attribute
            //
            MDataHandle outColorHandle = block.outputValue( aOutColor, &status );
            CHECK_MSTATUS( status );
            MFloatVector& outColor = outColorHandle.asFloatVector();

            outColor = resultColor;     // Set the output value
            outColorHandle.setClean(); // Mark the output value as clean
        }


        // Set ouput transparency
        //
		if ( plug == aOutTransparency || plug.parent() == aOutTransparency )
        {
            MFloatVector& transparency = block.inputValue( aInTransparency, &status ).asFloatVector();
            CHECK_MSTATUS( status );


            // Get the handle to the attribute
            //
            MDataHandle outTransHandle = block.outputValue( aOutTransparency, &status );
            CHECK_MSTATUS( status );
            MFloatVector& outTrans = outTransHandle.asFloatVector();

            outTrans = transparency;   // Set the output value
            outTransHandle.setClean(); // Mark the output value as clean
        }
    }
    else
    {
        return( MS::kUnknownParameter ); // We got an unexpected plug
    }

    return( MS::kSuccess );
}


