// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

#include <array>
#include <chrono>
#include <optional>
#include <algorithm>
#include <numeric>
#include <limits>

namespace me
{
	namespace stats
	{
		struct RateCapture
		{
			float average;
			float median;
			size_t samples;
			size_t sample_size;
			size_t rate;

			bool ExceedsSamples() const
			{
				return samples == std::numeric_limits<size_t>::max();
			}
		};

		/// <summary>
		///	Used to determine the rate of something over a number of samples. For example, frames per second or updates per second.
		/// </summary>
		/// <typeparam name="T_Sample"></typeparam>
		template<size_t T_SampleSize, size_t T_SampleRate = 1>
		class Rate
		{
		public:
			Rate()
				: m_tick {}
				, m_next_index{}
				, m_samples{}
				, m_last_mark{}
				, m_rate_sample{}
				, m_mark{}
				, m_scratch{}
			{
			}

			bool IsValid()
			{
				if (T_SampleSize > 0 && T_SampleRate > 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			void Mark()
			{
				// Ensure we are not trying to sample or rate at zero, which would cause a divide by zero error.
				if (T_SampleSize == 0 || T_SampleRate == 0)
				{
					return;
				}

				auto current_mark = std::chrono::high_resolution_clock::now();
				
				const auto marked = m_last_mark.has_value();

				// If we have not marked before, we cannot compute a delta, so just return.
				if (!m_last_mark)
				{
					m_last_mark = current_mark;
					return;
				}

				std::chrono::duration<float> delta = current_mark - *m_last_mark;
				m_last_mark = current_mark;

				m_rate_sample += delta;

				m_tick++;
				if (m_tick >= T_SampleRate)
				{
					m_tick = 0;

					auto average = m_rate_sample.count() / T_SampleRate;
					m_mark[m_next_index++] = average;
					m_rate_sample = {};

					if (m_next_index >= T_SampleSize)
					{
						m_next_index = 0;
					}

					if (m_samples != std::numeric_limits<size_t>::max())
					{
						m_samples++;
					}
				}
			}

			void Reset()
			{
				// Avoiding resetting the array, as it is not necessary and would be a performance hit.
				m_samples = 0;
				m_last_mark.reset();
				m_rate_sample.reset();
			}

			RateCapture Capture()
			{
				if (T_SampleSize == 0 || T_SampleRate == 0 || m_samples == 0)
				{
					return {};
				}

				// Reset our last mark time so we do not have a large delta when we mark again after computing the rate.
				m_last_mark.reset();

				const size_t count = std::min(m_samples, T_SampleSize);
				std::copy(m_mark.begin(), m_mark.begin() + count, m_scratch.begin());
				auto mid_itr = m_scratch.begin() + count / 2;
				std::nth_element(m_scratch.begin(), mid_itr, m_scratch.begin() + count);
				const float sum = std::accumulate(m_mark.begin(), m_mark.begin() + count, 0.0f);
				float median = *mid_itr;

				if (count % 2 == 0)
				{
					auto left_itr = std::max_element(m_scratch.begin(), mid_itr);
					median = (*left_itr + *mid_itr) * 0.5f;
				}

				RateCapture capture;
				capture.average = sum / count;
				capture.median = median;
				capture.samples = m_samples;
				capture.sample_size = T_SampleSize;
				capture.rate = T_SampleRate;
				return capture;
			}

		private:
			size_t m_tick;
			size_t m_next_index;
			size_t m_samples;
			std::optional<std::chrono::high_resolution_clock::time_point> m_last_mark;
			std::chrono::duration<float> m_rate_sample;
			alignas(64) std::array<float, T_SampleSize> m_mark;
			alignas(64) std::array<float, T_SampleSize> m_scratch;
		};
	}
}