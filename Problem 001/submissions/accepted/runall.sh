for i in ../../data/secret/*.in; do
  echo "Checking $i"
  echo "   John java:"
  java JohnPetri < $i > ans
  diff ${i%in}ans ans
  echo "   John C++:"
  ./johnPetri < $i > ans
  diff ${i%in}ans ans
  echo "   Sean C++:"
  ./seansheba < $i > ans
  diff ${i%in}ans ans
  echo "   Bob java:"
  java Amoeba < $i > ans
  diff ${i%in}ans ans
done
