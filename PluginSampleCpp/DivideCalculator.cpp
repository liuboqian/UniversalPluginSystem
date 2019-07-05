#include "stdafx.h"
#include "DivideCalculator.h"


DivideCalculator::DivideCalculator()
{
	_name = L"DivideCalculator";
}

DivideCalculator::~DivideCalculator()
{
}

const std::wstring DivideCalculator::name()
{
	return _name;
}

void DivideCalculator::set(const std::wstring & param)
{
	throw "not implemented";
}

void DivideCalculator::unset(const std::wstring & param)
{
	throw "not implemented";
}

const std::wstring DivideCalculator::invoke(const std::wstring & param)
{
	Parameter p;
	p.deserialize(param);
	auto result = p.getA() / p.getB();
	Result resObj;
	resObj.setResult(result);
	return resObj.serialize();
}
