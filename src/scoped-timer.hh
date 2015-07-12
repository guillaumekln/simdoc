#ifndef SCOPED_TIMER_HH
# define SCOPED_TIMER_HH

# include <string>
# include <chrono>

class ScopedTimer
{
public:
  ScopedTimer(const std::string& job)
    : _t0(std::chrono::steady_clock::now())
    , _job(job)
  {
    if (!_job.empty())
      std::cerr << job << "... ";
  }

  ~ScopedTimer()
  {
    auto diff = std::chrono::steady_clock::now() - _t0;
    double ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

    if (!_job.empty())
      std::cerr << "done in " << ms / 1000.0 << " seconds." << std::endl;
  }

private:
  std::chrono::steady_clock::time_point _t0;
  std::string _job;
};

# endif /* !SCOPED_TIMER_HH */
