#ifndef TIMER_HH
# define TIMER_HH

# include <string>
# include <chrono>

class Timer
{
public:
  Timer(const std::string& job)
    : _t0(std::chrono::steady_clock::now())
    , _job(job)
  {
    if (!_job.empty())
      std::cerr << job << "... ";
  }

  ~Timer()
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

# endif /* !TIMER_HH */
