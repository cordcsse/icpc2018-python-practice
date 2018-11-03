for i in ../data/sample/*.in; do
  echo "Checking $i"
  echo "   John's checker:"
  java JohnChecker < $i
  echo "   Bob's checker:"
  java verify < $i
done

for i in ../data/secret/*.in; do
  echo "Checking $i"
  echo "   John's checker:"
  java JohnChecker < $i
  echo "   Bob's checker:"
  java verify < $i
done
