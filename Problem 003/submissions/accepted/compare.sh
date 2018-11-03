for i in ../../data/sample/*.in; do
  echo "Comparing $i"
  echo "  Bob matrix closure:"
  time java IsaHasa < $i > ans
  diff ${i%in}ans ans
  echo "  John's solution:"
  time ./johnIsa < $i > ans
  diff ${i%in}ans ans
  echo "  Bob's graph closure:"
  time java GraphClosure < $i > ans
  diff ${i%in}ans ans
done
for i in ../../data/secret/*.in; do
  echo "Comparing $i"
  echo "  Bob matrix closure:"
  time java IsaHasa < $i > ans
  diff ${i%in}ans ans
  echo "  John's solution:"
  time ./johnIsa < $i > ans
  diff ${i%in}ans ans
  echo "  Bob's graph closure:"
  time java GraphClosure < $i > ans
  diff ${i%in}ans ans
done
