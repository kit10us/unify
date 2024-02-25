#include <unify/IExceptionHandler.h>

namespace unify
{
	/// <summary>
	/// Default exception handler for execution exceptions/failures.
	/// </summary>
	class DefaultExceptionHandler : public IExceptionHandler
	{
	public:
		void Throw(std::exception exception) override
		{
			throw exception;
		}
	};
}