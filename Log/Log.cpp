#include "Log.h"
#include <sstream>
#include <cstdarg>
#include <fstream>

#define MAX_MESSAGE_SIZE 8192

Log::Log()
    : m_current_buffer_id(0)
{
    std::fstream file("C:\\temp\\log.txt", std::ios::in | std::ios::out);
    m_config.Open(std::move(file));
}

Log::~Log()
{
    m_config.Save();
    m_config.Close();
}

void Log::SetMemoryThresholdMB(uint32_t mb)
{
    Entry::SetMemoryThresholdMB(mb);
}

void Log::Write(const std::string& domain, LogSeverity severity, const std::wstring& file, const std::string& line, const std::wstring& format, ...)
{
    if (!m_config.IsDomainEnabled(domain) || !m_config.IsSeverityEnabled(severity))
        return;
    wchar_t message[MAX_MESSAGE_SIZE] = {};
    va_list args;
    va_start(args, message);
    vswprintf(message, MAX_MESSAGE_SIZE - 1, format.c_str(), args);
    va_end(args);
    Entry::Ptr entry = Entry::Create(domain, severity, file, line, message);
    if (entry)
    {
        m_buffers[m_current_buffer_id].Push(entry);
    }
    else
    {
        m_buffers[m_current_buffer_id].Flush();
        m_current_buffer_id = (m_current_buffer_id + 1) % 2;
    }
}
