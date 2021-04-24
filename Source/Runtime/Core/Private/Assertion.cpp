#include "Assertion.h"
#include "Logger.h"

#ifndef NDEBUG

void Impl::LogToFail(bool isCritical, const Char* expr, const Char* file, BSBase::int32 line, const String& msg) noexcept
{
	static Logger assertLogger{ STR("Assert") };
	static Logger ensureLogger{ STR("Ensure") };
	static bool bInit = false;

	if (!bInit)
	{
		assertLogger.AddSink<Sink::FileSink>(STR("Assert.log"));
		ensureLogger.AddSink<Sink::FileSink>(STR("Ensure.log"));

		assertLogger.AddSink<Sink::StderrSink>();
		ensureLogger.AddSink<Sink::StderrSink>();
		
		bInit = true;
	}

	if (isCritical)
	{
		assertLogger.Log(LogVerbosity::Critical,
			STR("{} failed: {} {}, file: {}, line: {}"),
			isCritical ? STR("Assert") : STR("Ensure"), expr, msg, file, line
		);
	}
	else
	{
		ensureLogger.Log(LogVerbosity::Error,
			STR("{} failed: {} {}, file: {}, line: {}"),
			isCritical ? STR("Assert") : STR("Ensure"), expr, msg, file, line
		);
	}
}

#endif
