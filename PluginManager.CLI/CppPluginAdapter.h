#pragma once

#include "../PluginManager.Core/IPlugin.h"

namespace UPS {
	namespace CLI {
		public ref class CppPluginAdapter :CSharp::IPlugin
		{
		public:
			// this function pass in a pointer, but it will add ref count
			CppPluginAdapter(std::shared_ptr<IPlugin>* plugin);
			~CppPluginAdapter();
			std::shared_ptr<IPlugin> get();

			// Inherited via IPlugin
			virtual System::String ^ Name();
			virtual void Set(System::String ^param);
			virtual void Unset(System::String ^param);
			virtual System::String ^ Invoke(System::String ^param);

		private:
			std::shared_ptr<IPlugin>* _plugin;
		};

	}
}

