#!/bin/bash

# === CONFIGURATION ===
MINISHELL=../minishell
LOG_DIR=tests_logs
PROMPT="minishell: "

# === LISTE DES TESTS ===
declare -a CMD_LIST=(
	"echo hello world | cat -e"
	"pwd"
	"ls | grep test"
	"export VAR=42 | echo \$VAR"
	"unset VAR | echo \$VAR"
)

declare -a EXPECTED_LIST=(
	"hello world$"
	"$(pwd)"
	"$(ls | grep test)"
	"42"
	""
)

# === PRÉPARATION ===
mkdir -p "$LOG_DIR"
> "$LOG_DIR/result.log"

OK=0
KO=0

echo "===== Lancement des tests Minishell ====="
echo

# === BOUCLE DE TESTS ===
for ((i=0; i<${#CMD_LIST[@]}; i++)); do
	cmd="${CMD_LIST[$i]}"
	expected="${EXPECTED_LIST[$i]}"

	echo "[$((i+1))] Test : $cmd"

	# Exécution dans minishell
	# On supprime le prompt, les lignes contenant "exit", et les lignes qui reprennent la commande
	output=$(echo "$cmd" | $MINISHELL 2>/dev/null \
		| sed "s/^$PROMPT//g" \
		| grep -v "^exit$" \
		| grep -v "^$cmd$" \
		| tr -d '\r')

	# Supprimer les prompts restants éventuellement à la fin
	output=$(echo "$output" | sed "s/$PROMPT//g")

	# Comparaison avec le résultat attendu
	if [ "$output" = "$expected" ]; then
		echo "✅ OK"
		echo "[$((i+1))] OK : $cmd" >> "$LOG_DIR/result.log"
		OK=$((OK+1))
	else
		echo "❌ KO"
		echo "[$((i+1))] KO : $cmd" >> "$LOG_DIR/result.log"
		echo "---- Expected ----" >> "$LOG_DIR/result.log"
		echo "$expected" >> "$LOG_DIR/result.log"
		echo "---- Got ----" >> "$LOG_DIR/result.log"
		echo "$output" >> "$LOG_DIR/result.log"
		echo >> "$LOG_DIR/result.log"
		KO=$((KO+1))
	fi
	echo
done

# === RÉSUMÉ FINAL ===
echo "===== Résumé ====="
echo "✅ OK : $OK"
echo "❌ KO : $KO"
echo
echo "Résultats détaillés dans : $LOG_DIR/result.log"

echo
echo "===== Commandes testées et résultats attendus ====="
for ((i=0; i<${#CMD_LIST[@]}; i++)); do
	echo "cmd=${CMD_LIST[$i]}"
	echo "res=${EXPECTED_LIST[$i]}"
	echo
done
