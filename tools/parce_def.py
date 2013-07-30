#! /usr/bin/env python

import sys
import re

#---------------------------------------------------------
#---------------------------------------------------------
class MemberType:
	Function 	= "Function"
	Field 		= "Field"
	
#---------------------------------------------------------
#---------------------------------------------------------
class MemberAccess:
	values = ( 	{ "name":"Private", 	"re":"private" },
	 	 		{ "name":"Public", 		"re":"public" },
				{ "name":"Protected", 	"re":"protected" } )

	def getAccess(self, definition):
		defcp = definition
		res = "Private"
		for val in self.values:
			if re.search(val["re"], defcp) != None:
				defcp = re.sub(val["re"], "", defcp).strip()
				res = val["name"]
				break
		return ( defcp, res )
		
	
#---------------------------------------------------------
#---------------------------------------------------------
class MemberFlags:
	values = (	{ "name":"Native",		"re":"native" },
				{ "name":"Static",		"re":"static" },
				{ "name":"Final",		"re":"final" },
				{ "name":"Abstract",	"re":"abstract" } )

	def getFlags(self, definition):
		defcp = definition
		res = []
		for val in self.values:
			if re.search(val["re"], defcp) != None:
				defcp = re.sub(val["re"], "", defcp).strip()
				res.append(val["name"])
		return ( defcp, res )

#---------------------------------------------------------
#---------------------------------------------------------
class FunctionType:
	values = (	{ "name":"Void",		"re":"\)V" },
				{ "name":"Boolean",		"re":"\)Z" },
				{ "name":"Byte",		"re":"\)B" },
				{ "name":"Char",		"re":"\)C" },
				{ "name":"Short",		"re":"\)S" },
				{ "name":"Int",			"re":"\)I" },
				{ "name":"Long",		"re":"\)J" },
				{ "name":"Float",		"re":"\)F" },
				{ "name":"Double",		"re":"\)D" },
				{ "name":"Object",		"re":"(\)L)|(\)\[)" } )

	def getFunctionType(self, signature):
		res = "Unknown"
		for val in self.values:
			if re.search(val["re"], signature) != None:
				res = val["name"]
				break
		return res

#---------------------------------------------------------
#---------------------------------------------------------
class MemberDefinition:
	definition  = ""
	type		= ""
	flags		= ""
	name		= ""
	signature	= ""
	functionType= ""

	def fieldName(self, definition):
		split = definition.split(" ")
		res = split[len(split) - 1].strip()
		res = re.sub(";", "", res)
		return res.strip()
	
	def functionName(self, definition):
		split = definition.split(" ")
		res = ""
		for s in split:
			if re.search(".*\(", s) != None:
				res = re.sub("\(.*", "", s)
				break
		return res.strip()

	def printStruct(self, uniq_name):
		print "  /* %s */" % self.definition
		print "  { 0, %s, %s, \"%s\", \"%s\", \"%s\" }," % \
			( self.functionType, self.flags, uniq_name, self.name, self.signature)

	def parceDefinition(self, definition, sig):
		self.definition = definition
		defcp = definition
		signature = sig
		functionType = "Unknown"

		access = MemberAccess()
		accessRet = access.getAccess(defcp)
		defcp = accessRet[0]
		accessStr = accessRet[1]
		
		memberFlags = MemberFlags()
		flagsRet = memberFlags.getFlags(defcp)
		defcp = flagsRet[0]
		flagsList = flagsRet[1]
		flagsList.append(accessStr)

		split = defcp.split(" ")
		if re.search(".+\(",split[0]) != None:
			flagsList.append("Constructor")
			name = "<init>"
			type = MemberType.Function
			ft = FunctionType()
			functionType = ft.getFunctionType(signature)
		else:
			if re.search("\(.*\)( throws.*)?;",defcp) != None:
				flagsList.append("Function")
				type = MemberType.Function
				name = self.functionName(defcp)
				ft = FunctionType()
				functionType = ft.getFunctionType(signature)
			else:
				flagsList.append("Field")
				type = MemberType.Field
				name = self.fieldName(defcp)

		flags = "|".join(flagsList)
		self.type = type
		self.flags = flags
		self.functionType = functionType
		self.name = name
		self.signature = signature

#---------------------------------------------------------
buffer = {}
members = []
names = []
uindex = 0

def uniq_name(member_name):
	global uindex
	if not member_name in names:
		names.append(member_name)
		return member_name
	else:
		ret = "{0}_{1}".format( member_name, uindex )
		uindex += 1
		return ret

def processSignature(definition, signature, uindex):
	split = signature.split(":")
	sig = split[len(split) - 1].strip()

	member = MemberDefinition()
	member.parceDefinition(definition, sig)
	members.append(member)

def processLine(index, line):
	buffer[index] = line
	if line.startswith("Signature:"):
		definition = buffer[index - 1].strip()
		processSignature(definition, line, index)

def main():
	input = sys.stdin
	index = 0
	for l in input:
		processLine(index,l.strip())
		index += 1

	for member in members:
		member.printStruct(uniq_name(member.name))

if __name__ == "__main__":
	main()

