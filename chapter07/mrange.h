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

}