echo "" > benchmark.txt
input=$1
for (( t=1; t<=16; t+=2 ))
do
    echo $t $(./vcf_parallel_reader -i $input -j $t ) >> benchmark.txt
done
