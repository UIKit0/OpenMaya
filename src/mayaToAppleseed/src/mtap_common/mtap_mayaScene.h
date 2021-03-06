#ifndef MTAP_MAYA_SCENE
#define MTAP_MAYA_SCENE

#include <maya/MDagPathArray.h>
#include <fstream>
#include <map>

#include "mayaScene.h"
#include "mtap_renderGlobals.h"
#include "mtap_MayaObject.h"
#include "../appleseed/appleseed.h"
#include "utilities/MiniMap.h"


class mtap_MayaScene : public MayaScene
{
public:
	AppleRender::AppleseedRenderer mtap_renderer;
	mtap_RenderGlobals *renderGlobals;
	MayaObject *defaultCamera; // needed for motionblur calculation
	
	MiniMap<MObject, MayaObject *> mayaObjMObjMap;

	virtual void transformUpdateCallback(MayaObject *);
	virtual void shapeUpdateCallback(MayaObject *);
	virtual bool translateShaders(int timeStep);
	virtual bool translateShapes(int timeStep);
	virtual bool doPreRenderJobs();
	virtual bool renderImage();
	virtual bool doPreFrameJobs();
	virtual bool doPostFrameJobs();
	virtual bool doPostRenderJobs();
	virtual MayaObject* mayaObjectCreator(MObject&);
	virtual MayaObject* mayaObjectCreator(MDagPath&);
	virtual void mayaObjectDeleter(MayaObject *);
	virtual void getRenderGlobals();
	virtual void stopRendering();
	virtual void updateInteraciveRenderScene(std::vector<MObject> mobjList);
	virtual void userThreadProcedure();
	void mobjectListToMayaObjectList(std::vector<MObject>& mObjectList, std::vector<MayaObject *>& mtapObjectList);
	virtual bool postParseCallback();
	void makeMayaObjectMObjMap(); // fill with maya objects and dag nodes for later fast access
	mtap_MayaObject *getMayaObjectFromMap(MObject& mobj);
	bool parseScene();
	void createObjAssembly(mtap_MayaObject *obj);
	void createObjAssemblyInstances(mtap_MayaObject *obj);
	asr::Assembly *createAssembly(mtap_MayaObject *obj);
	asr::Assembly *getAssembly(mtap_MayaObject *obj);
	mtap_MayaScene();
	~mtap_MayaScene();
};


#endif
