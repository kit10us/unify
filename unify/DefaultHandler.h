#include <unify/IExceptionHandler.h>

namespace unify
{
	class DefaultExceptionHandler : public IExceptionHandler
	{
	public:
		void Throw(std::exception exception) override
		{
			throw exception;
		}
	};
}