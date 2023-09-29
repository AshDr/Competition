#!/bin/zsh
# remove useless file in subdir, e.g. cpp:tests,executable file etc
#
if ! which fd
then
  echo "can't find fd"
else
  echo "find fd!"
fi

SAVEIFS=$IFS
IFS=$(echo -en "\n\b")
declare -a results=(`fd -t d`)

#echo ${results}
curpath=$(pwd)
for subdir in ${results[@]};
do
  cd $subdir;
  res=$(find  )
  echo $res
  #cd $curpath;
done
