#include <algorithm>

namespace mrange {

template<typename Container>
struct Range
{
   typename Container::iterator begin;
   typename Container::iterator end;

   Range(Container& container)
      : begin {container.begin()}
      , end {container.end()}
   {
   }
};

// maybe this is easier because you don't need to specify template arguments
template<typename Container>
Range<Container> MakeRange(Container& container)
{
   return {container};
}

template<typename RangeType, typename TransformFunctionType>
void Transform(RangeType& range, TransformFunctionType transformFunction)
{
   for(auto iter {range.begin}; iter != range.end; ++iter)
   {
      *iter = transformFunction(*iter);
   }
}

template<typename Iterator, typename PredicateFunctionType>
class FilterIterator
{
public:
   FilterIterator(Iterator iterator, Iterator end, PredicateFunctionType predicate)
      : m_currentPosition{iterator}
      , m_end{end}
      , m_predicate{predicate}
      {
         if(!m_predicate(*m_currentPosition))
         {
            this->Increment();
         }
      }

   auto& operator++()
   {
      return this->Increment();
   }

   auto operator*()
   {
      return *m_currentPosition;
   }

private:
   Iterator m_currentPosition;
   Iterator m_end;
   PredicateFunctionType m_predicate;

   auto& Increment()
   {
      ++m_currentPosition;
      m_currentPosition = std::find_if(m_currentPosition, m_end, m_predicate);
      return *this;
   }
};

}