#pragma once
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <memory>

#define PREVENT_COPY(className) \
    className(const className&); \
    className& operator=(const className&);

class Log;

enum class LogSeverity
{
    Error,
    Warning,
    Info,
    Debug
};

class LogUtils
{
protected:
    class Config
    {
    public:
        Config();
        ~Config();
        bool Open(std::iostream&& stream);
        void Close();
        bool Save();

        bool IsSeverityEnabled(LogSeverity severity);
        bool IsDomainEnabled(const std::string& domain);
    private:
        std::istream                            m_stream;
        std::vector<uint32_t>                   m_severity_enabled;
        std::unordered_map<std::string, bool>   m_domain_enabled;

        PREVENT_COPY(Config);
    };

    // Holder for log entry
    class Entry
    {
    public:
        typedef std::shared_ptr<Entry> Ptr;

        Entry();
        ~Entry();

        void                Release();
        void                Write(std::ostream stream);
        static Entry::Ptr   Create(const std::string& domain, LogSeverity severity, const std::wstring& filename, const std::string& line, const std::wstring& message);
        static void         SetMemoryThresholdMB(uint32_t mb);
    private:
        std::string         m_domain;
        LogSeverity         m_severity;
        std::wstring        m_filename;
        std::string         m_line;
        std::wstring        m_message;

        PREVENT_COPY(Entry)
    };

    // Container of log entries
    class Stream
    {
    public:
        Stream();
        ~Stream();

        bool Push(Entry::Ptr& entry);
        void Flush();
    private:
        PREVENT_COPY(Stream);
    };

    // Balances a few per-thread streams and correctly flushes them to file
    class StreamBuffer
    {
    public:
        StreamBuffer();
        ~StreamBuffer();

        bool Push(Entry::Ptr& entry);
        void Flush();
    private:
        PREVENT_COPY(StreamBuffer);
    };
};


class Log : protected LogUtils
{
public:
    void SetMemoryThresholdMB(uint32_t mb);
    void Write(const std::string& domain, LogSeverity severity, const std::wstring& filename, const std::string& line, const std::wstring& format, ...);

    static Log& Instance();
private:
    Log();

    uint32_t                m_current_buffer_id;
    LogUtils::StreamBuffer  m_buffers[2];
    LogUtils::Config        m_config;
    PREVENT_COPY(Log);
};

//#define Z_ERROR(domain, ...)   Log::Write(domain, Log::Severity::Error,     __FILE__, __LINE__, __VA_ARGS__);
//#define Z_WARNING(domain, ...) Log::Write(domain, Log::Severity::Warning,   __FILE__, __LINE__, __VA_ARGS__);
//#define Z_INFO(domain, ...)    Log::Write(domain, Log::Severity::Info,      __FILE__, __LINE__, __VA_ARGS__);
//#define Z_DEBUG(domain, ...)   Log::Write(domain, Log::Severity::Debug,     __FILE__, __LINE__, __VA_ARGS__);