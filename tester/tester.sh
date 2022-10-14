	testnbr=$(ls in | wc -l)
	testact=2


	ARG=in/test$testact
	cat $ARG |  xargs ./tester <infile/infile1 2>out/minishell/test$testact 1>>out/minishell/test$testact
	ARG=in/test$testact
	bash $ARG <infile/infile1 2>out/bash/test$testact 1>>out/bash/test$testact
	echo yes
