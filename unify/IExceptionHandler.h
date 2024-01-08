#include <exception>
#include <memory>

namespace unify
{
	class IExceptionHandler
	{
	public:
		typedef std::shared_ptr<IExceptionHandler> ptr;
		typedef std::weak_ptr<IExceptionHandler> weak_ptr;

		virtual void Throw(std::exception exception) = 0;
	};
}