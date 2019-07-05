#pragma once
#include "CppPluginAdapter.h"
#include "../PluginManager.Core/PluginManagerFactory.h"

namespace UPS {
	namespace CLI {
		public ref class PluginManagerFactoryWrapper
		{
		public:
			PluginManagerFactoryWrapper();
			~PluginManagerFactoryWrapper();
			void loadPluginManagers();  // load all plugin managers in this folder, won't be loaded if they don't have the three global functions or already been loaded
 			cli::array<UPS::CSharp::IPlugin^>^ getAllPlugins();
			cli::array<System::String^>^ getAllPluginNames();
			UPS::CSharp::IPlugin^ getPlugin(System::String^ name);
			void releaseAll();
			void composeAll();
			cli::array<System::String^>^ getGlobalParts();
			void addGlobalPart(System::String^ part);
			void removeGlobalPart(System::String^ part);
			void clearGlobalPart();
			std::shared_ptr<PluginManagerFactory> getInstance();
		};
	}
}

