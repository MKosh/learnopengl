mkdir ${1}
cp utils/template.cc ${1}
mv ${1}/template.cc ${1}/${1}.cc
cp utils/*.shader ${1}
cp utils/Makefile ${1}

sed -i "s/template/${1}/g" ${1}/Makefile


