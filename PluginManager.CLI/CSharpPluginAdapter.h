#pragma once

#include "../PluginManager.Core/IPlugin.h"
#include <msclr/auto_gcroot.h>

namespace UPS {
	namespace CLI {
		public class CSharpPluginAdapter
			: public UPS::IPlugin
		{
		public:
			CSharpPluginAdapter(UPS::CSharp::IPlugin^ plugin);
			~CSharpPluginAdapter();
			UPS::CSharp::IPlugin^ get();

			// Inherited via IPlugin
			virtual const std::wstring name() override;
			virtual void set(const std::wstring & param) override;
			virtual void unset(const std::wstring & param) override;
			virtual const std::wstring invoke(const std::wstring & param) override;

		private:
			msclr::auto_gcroot<UPS::CSharp::IPlugin^> _plugin;

		};
	}
}

