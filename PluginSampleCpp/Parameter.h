#pragma once

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"
#include <iostream>

//! GenericDocument with UTF16 encoding
typedef rapidjson::GenericDocument<rapidjson::UTF16<> > WDocument;
typedef rapidjson::GenericStringBuffer<rapidjson::UTF16<> > WStringBuffer;

class ISerializable {
public:
	virtual std::wstring serialize() = 0;
	virtual void deserialize(const std::wstring& jsonStr) = 0;
};

class Parameter :ISerializable {
public:
	double getA() { return _a; }
	void setA(double a) { _a = a; }
	double getB() { return _b; }
	void setB(double b) { _b = b; }

	std::wstring serialize() override {
		WStringBuffer buffer;
		rapidjson::Writer<WStringBuffer> writer(buffer);

		writer.StartObject();
		writer.Key("a");
		writer.Double(getA());
		writer.Key("b");
		writer.Double(getB());
		writer.EndObject();

		return buffer.GetString();
	}

	void deserialize(const std::wstring& jsonStr) override {
		WDocument doc;
		doc.Parse(jsonStr.c_str());
		if (!doc.IsObject())
			throw "Wrong json string";
		auto& varA = doc[L"a"];
		auto& varB = doc[L"b"];
		setA(varA.GetDouble());
		setB(varB.GetDouble());
	}

private:
	double _a;
	double _b;
};

class Result :ISerializable {
public:
	Result() {}
	double getResult() { return _result; }
	void setResult(double r) { _result = r; }

	std::wstring serialize() override {
		WStringBuffer buffer;
		rapidjson::Writer<WStringBuffer> writer(buffer);
		writer.Double(_result);
		return buffer.GetString();
	}

	void deserialize(const std::wstring& jsonStr) override {
		WDocument doc;
		doc.Parse(jsonStr.c_str());
		if (!doc.IsDouble())
			throw "Wrong json string";
		_result = doc.GetDouble();
	}

private:
	double _result;
};