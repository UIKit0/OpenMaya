#ifndef MTM_ATTR_TOOLS_H
#define MTM_ATTR_TOOLS_H

#include <maya/MPlug.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MString.h>
#include <maya/MColor.h>
#include <maya/MVector.h>
#include <maya/Mpoint.h>


bool getFloat(MString& plugName, MFnDependencyNode& dn, float& value);

bool getFloat(const char* plugName, MFnDependencyNode& dn, float& value);

bool getFloat2(MString& plugName, MFnDependencyNode& dn, float2& value);

bool getFloat2(MString& plugName, MFnDependencyNode& dn, MVector& value);

bool getDouble(MString& plugName, MFnDependencyNode& dn, double& value);

bool getString(MString& plugName, MFnDependencyNode& dn, MString& value);

bool getInt(MString& plugName, MFnDependencyNode& dn, int& value);

bool getInt(const char *plugName, MFnDependencyNode& dn, int& value);

bool getUInt(const char *plugName, MFnDependencyNode& dn, uint& value);

bool getBool(MString& plugName, MFnDependencyNode& dn, bool& value);

bool getBool(const char *plugName, MFnDependencyNode& dn, bool& value);

bool getEnum(MString& plugName, MFnDependencyNode& dn, int& value);

bool getEnum(MString& plugName, MFnDependencyNode& dn, int& id, MString& value);

bool getEnum(const char *plugName, MFnDependencyNode& dn, int& id, MString& value);

bool getInt2(MString& plugName, MFnDependencyNode& dn, int2& value);

bool getLong(MString& plugName, MFnDependencyNode& dn, long& value);

bool getColor(MString& plugName, MFnDependencyNode& dn, MColor& value);

bool getColor(MString& plugName, MFnDependencyNode& dn, MString& value);

bool getColor(const char *plugName, MFnDependencyNode& dn, MColor& value);

bool getColor(const char *plugName, MFnDependencyNode& dn, MString& value);

bool getVector(MString& plugName, MFnDependencyNode& dn, MVector& value);

bool getPoint(MString& plugName, MFnDependencyNode& dn, MPoint& value);

bool getPoint(MString& plugName, MFnDependencyNode& dn, MVector& value);

bool getMsgObj(const char *plugName, MFnDependencyNode& dn, MObject& value);

#endif
