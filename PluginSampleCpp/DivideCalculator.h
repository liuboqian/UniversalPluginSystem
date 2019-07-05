#pragma once
#include "../PluginManager.Core/IPlugin.h"
#include "Parameter.h"

class DivideCalculator : public UPS::IPlugin
{
public:
	DivideCalculator();
	~DivideCalculator();

	// Inherited via IPlugin
	virtual const std::wstring name() override;
	virtual void set(const std::wstring & param) override;
	virtual void unset(const std::wstring & param) override;
	virtual const std::wstring invoke(const std::wstring & param) override;

private:
	std::wstring _name;
};

