#pragma once

#include <vector>

#include "CSharpPluginAdapter.h"
#include "../PluginManager.Core/PluginManagerBase.h"
#include "../PluginManager.Core/PluginManagerFactory.h"
#include "PluginManagerFactoryWrapper.h"

#include <msclr/auto_gcroot.h>   // this header file must be put behind #using, or it will cause a fatal compile error

namespace UPS
{
	namespace CLI
	{
		public class PluginManagerCSAdapter 
			: public PluginManagerBase
		{
		public:
			static PluginManagerCSAdapter* createPluginManager(bool allplatform);
			static void deletePluginManager(PluginManagerCSAdapter* manager);
			// Inherited via PluginManagerBase
			virtual void setAllPlatform(bool allplatform) override;
			virtual void compose() override;
			virtual void releasePlugins() override;
			virtual std::vector<std::wstring> getPluginNames() const override;
			virtual std::shared_ptr<IPlugin> getPluginInternal(std::wstring name) const override;
			virtual void addPart(const std::wstring& part) override;
			virtual void removePart(const std::wstring& part) override;
			virtual void clearParts() override;
			void injectCSManager(intptr_t manager);
		private:
			PluginManagerCSAdapter(bool allplatform);
			~PluginManagerCSAdapter();
			msclr::auto_gcroot<UPS::CSharp::PluginManagerCSharp^> _csmanager;
			msclr::auto_gcroot<UPS::CLI::PluginManagerFactoryWrapper^> _factoryWrapper;
		};
	}
}

