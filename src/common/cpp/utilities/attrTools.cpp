#include <maya/MStatus.h>
#include <maya/MDGContext.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MPlugArray.h>

#include "attrTools.h"

bool getFloat(MString& plugName, MFnDependencyNode& dn, float& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	value = plug.asFloat(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getFloat(const char* plugName, MFnDependencyNode& dn, float& value)
{
	return getFloat(MString(plugName), dn, value);
}

bool getFloat2(MString& plugName, MFnDependencyNode& dn, float2& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MString pName0 = plugName + "0";
	MString pName1 = plugName + "1";
	if( plugName == "repeatUV")
	{
		pName0 = "repeatU";
		pName0 = "repeatV";
	}
	MPlug plug = dn.findPlug(pName0, &stat);
	if( !stat )
		return false;
	value[0] = plug.asFloat(ctx, &stat);
	plug = dn.findPlug(pName0, &stat);
	if( !stat )
		return false;
	value[1] = plug.asFloat(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getFloat2(MString& plugName, MFnDependencyNode& dn, MVector& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName + "0", &stat);
	if( !stat )
		return false;
	value.x = plug.asFloat(ctx, &stat);
	plug = dn.findPlug(plugName + "1", &stat);
	if( !stat )
		return false;
	value.y = plug.asFloat(ctx, &stat);
	if(stat)
		return true;
	return result;
}


bool getDouble(MString& plugName, MFnDependencyNode& dn, double& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	value = plug.asDouble(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getString(MString& plugName, MFnDependencyNode& dn, MString& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	value = plug.asString(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getLong(MString& plugName, MFnDependencyNode& dn, long& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	value = plug.asInt(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getInt(MString& plugName, MFnDependencyNode& dn, int& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	value = plug.asInt(ctx, &stat);
	if(stat)
		return true;
	return result;
}
bool getInt(const char *plugName, MFnDependencyNode& dn, int& value)
{
	return getInt(MString(plugName), dn, value);
}

bool getUInt(const char *plugName, MFnDependencyNode& dn, uint& value)
{
	int val = value;
	bool ret = getInt(MString(plugName), dn, val);
	value = val;
	return ret;
}

bool getBool(MString& plugName, MFnDependencyNode& dn, bool& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	value = plug.asBool(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getBool(const char *plugName, MFnDependencyNode& dn, bool& value)
{
	return getBool(MString(plugName), dn, value);
}

bool getEnum(MString& plugName, MFnDependencyNode& dn, int& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	value = plug.asShort(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getEnum(MString& plugName, MFnDependencyNode& dn, int& id, MString& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	id = plug.asShort(ctx, &stat);
	if(!stat)
		return false;
	MFnEnumAttribute eAttr(plug.attribute(&stat));
	if(!stat)
		return false;
	value = eAttr.fieldName(id, &stat);
	if(!stat)
		return false;
	return true;
}

bool getEnum(const char *plugName, MFnDependencyNode& dn, int& id, MString& value)
{
	return getEnum(MString(plugName), dn, id, value);
}

bool getInt2(MString& plugName, MFnDependencyNode& dn, int2& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName + "0", &stat);
	if( !stat )
		return false;
	value[0] = plug.asInt(ctx, &stat);
	plug = dn.findPlug(plugName + "1", &stat);
	if( !stat )
		return false;
	value[1] = plug.asInt(ctx, &stat);
	if(stat)
		return true;
	return result;
}

bool getColor(MString& plugName, MFnDependencyNode& dn, MColor& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	float r, g, b;
	MPlug plug = dn.findPlug(plugName + "R", &stat);
	if( !stat ) return false;
	r = plug.asFloat(ctx, &stat);
	plug = dn.findPlug(plugName + "G", &stat);
	if( !stat ) return false;
	g = plug.asFloat(ctx, &stat);
	plug = dn.findPlug(plugName + "B", &stat);
	if( !stat ) return false;
	b = plug.asFloat(ctx, &stat);
	value.r = r;
	value.g = g;
	value.b = b;
	if(stat) return true;
	return result;
}

bool getColor(const char *plugName, MFnDependencyNode& dn, MColor& value)
{
	return getColor(MString(plugName), dn, value);
}

bool getColor(MString& plugName, MFnDependencyNode& dn, MString& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	float r, g, b;
	MPlug plug = dn.findPlug(plugName + "R", &stat);
	if( !stat ) return false;
	r = plug.asFloat(ctx, &stat);
	plug = dn.findPlug(plugName + "G", &stat);
	if( !stat ) return false;
	g = plug.asFloat(ctx, &stat);
	plug = dn.findPlug(plugName + "B", &stat);
	if( !stat ) return false;
	b = plug.asFloat(ctx, &stat);
	value = MString("") + r + " " + g + " " + b;
	result = true;
	return result;
}

bool getColor(const char *plugName, MFnDependencyNode& dn, MString& value)
{
	return getColor(MString(plugName), dn, value);
}

bool getVector(MString& plugName, MFnDependencyNode& dn, MVector& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	MPlug Xplug = dn.findPlug(plugName + "X", &stat);
	MPlug Yplug = dn.findPlug(plugName + "Y", &stat);
	MPlug Zplug = dn.findPlug(plugName + "Z", &stat);
	if( !stat )
		return false;
	value.x = Xplug.asDouble(ctx, &stat);
	value.y = Yplug.asDouble(ctx, &stat);
	value.z = Zplug.asDouble(ctx, &stat);
	if( !stat )
		return false;
	return true;
}

bool getPoint(MString& plugName, MFnDependencyNode& dn, MPoint& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	MPlug Xplug = dn.findPlug(plugName + "X", &stat);
	MPlug Yplug = dn.findPlug(plugName + "Y", &stat);
	MPlug Zplug = dn.findPlug(plugName + "Z", &stat);
	if( !stat )
		return false;
	value.x = Xplug.asDouble(ctx, &stat);
	value.y = Yplug.asDouble(ctx, &stat);
	value.z = Zplug.asDouble(ctx, &stat);
	if( !stat )
		return false;
	return true;
}

bool getPoint(MString& plugName, MFnDependencyNode& dn, MVector& value)
{
	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	MPlug Xplug = dn.findPlug(plugName + "X", &stat);
	MPlug Yplug = dn.findPlug(plugName + "Y", &stat);
	MPlug Zplug = dn.findPlug(plugName + "Z", &stat);
	if( !stat )
		return false;
	value.x = Xplug.asDouble(ctx, &stat);
	value.y = Yplug.asDouble(ctx, &stat);
	value.z = Zplug.asDouble(ctx, &stat);
	if( !stat )
		return false;
	return true;
}

bool getMsgObj(const char *plugName, MFnDependencyNode& dn, MObject& value)
{
	value = MObject::kNullObj;

	MDGContext ctx = MDGContext::fsNormal;
	MStatus stat = MS::kSuccess;
	bool result = false;
	MPlug plug = dn.findPlug(plugName, &stat);
	if( !stat )
		return false;
	if(!plug.isConnected())
		return false;
	MPlugArray inConnections;
	plug.connectedTo(inConnections, true, false, &stat);
	if( !stat )
		return false;
	value = inConnections[0].node();
	return true;
}
