using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using log4net;
using log4net.Config;

namespace UPS.CSharp
{
	public class Logger
	{
		public static ILog TextLogger => LogManager.GetLogger("UPS");

		static Logger()
		{
			BasicConfigurator.Configure();
		}

		public static void Info(string msg)
		{
			TextLogger.Info(msg);
		}

		public static void Debug(string msg, Exception e = null)
		{
			TextLogger.Debug(msg, e);
		}

		public static void Error(string msg, Exception e = null)
		{
			TextLogger.Error(msg, e);
		}
	}
}
