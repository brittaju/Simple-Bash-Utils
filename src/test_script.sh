CAT_BIN="cat/s21_cat"
GREP_BIN="grep/s21_grep"

# Папка с тестовыми файлами
TEST_DIR="test_files"

# Проверяем, существуют ли системные утилиты для сравнения
if ! command -v cat >/dev/null 2>&1 || ! command -v grep >/dev/null 2>&1; then
    echo "Error: System 'cat' or 'grep' not found. Please run this script on Linux, Mac or WSL."
    exit 1
fi

# Функция для красивого вывода разделителей
print_header() {
    echo "----------------------------------------"
    echo " $1 "
    echo "----------------------------------------"
}

# Функция сравнения двух файлов (diff)
compare_outputs() {
    local test_name=$1
    local my_output="out_my.txt"
    local sys_output="out_sys.txt"
    
    if diff -q "$my_output" "$sys_output" >/dev/null ; then
        echo "✅ TEST PASSED: $test_name"
    else
        echo "❌ TEST FAILED: $test_name"
        echo "--- YOUR OUTPUT ---"
        cat "$my_output"
        echo "--- SYSTEM OUTPUT ---"
        cat "$sys_output"
    fi
    echo ""
}

# --- ТЕСТЫ ДЛЯ UTILITY CAT ---
print_header "TESTING UTILITY CAT"

# Тест 1: Обычный вывод файла (cat file.txt)
echo "Test 1: Basic cat output"
$CAT_BIN $TEST_DIR/normal.txt > out_my.txt
cat $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Basic cat output"

# Тест 2: Нумерация строк (-n)
echo "Test 2: Line numbering (-n)"
$CAT_BIN -n $TEST_DIR/normal.txt > out_my.txt
cat -n $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Line numbering (-n)"

# Тест 3: Отображение табуляций (-t)
echo "Test 3: Show tabs (-t)"
$CAT_BIN -t $TEST_DIR/normal.txt > out_my.txt
cat -t $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Show tabs (-t)"

# Тест 4: Нумерация непустых строк (-b)
echo "Test 4: Line numbering (-b)"
$CAT_BIN -b $TEST_DIR/normal.txt > out_my.txt
cat -b $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Line numbering (-b)"

# Тест 5: Конец строки (-e)
echo "Test 5: End of line (-e)"
$CAT_BIN -e $TEST_DIR/normal.txt > out_my.txt
cat -e $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "End of line (-e)"

# Тест 6: Сжатие строк (-s)
echo "Test 6: String compression (-s)"
$CAT_BIN -s $TEST_DIR/normal.txt > out_my.txt
cat -s $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "String compression (-s)"

# --- ТЕСТЫ ДЛЯ UTILITY GREP ---
print_header "TESTING UTILITY GREP"

# Тест 7: Простой поиск (grep pattern file)
echo "Test 7: Simple search"
$GREP_BIN "World" $TEST_DIR/normal.txt > out_my.txt
grep "World" $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Simple search"

# Тест 8: Инвертированный поиск (-v)
echo "Test 8: Inverted match (-v)"
$GREP_BIN -v "World" $TEST_DIR/normal.txt > out_my.txt
grep -v "World" $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Inverted match (-v)"

# Тест 9: Нумерация строк в выводе (-n)
echo "Test 9: Line numbers in output (-n)"
$GREP_BIN -n "World" $TEST_DIR/normal.txt > out_my.txt
grep -n "World" $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Line numbers in output (-n)"

# Тест 10: Шаблон (-e)
echo "Test 10: Pattern (-e)"
$GREP_BIN -e "World" $TEST_DIR/normal.txt > out_my.txt
grep -e "World" $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Pattern (-e)"

# Тест 11: Игнорирование различия регистра (-i)
echo "Test 11: Ignoring case differences (-i)"
$GREP_BIN -i "WORLD" $TEST_DIR/normal.txt > out_my.txt
grep -i "WORLD" $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Ignoring case differences (-i)"

# Тест 12: Количество совпадающих строк (-c)
echo "Test 12: Number of matching lines (-c)"
$GREP_BIN -c "World" $TEST_DIR/normal.txt > out_my.txt
grep -c "World" $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Number of matching lines (-c)"

# Тест 13: Совпадающие файлы (-l)
echo "Test 13: Matching files (-l)"
$GREP_BIN -l "World" $TEST_DIR/normal.txt > out_my.txt
grep -l "World" $TEST_DIR/normal.txt > out_sys.txt
compare_outputs "Matching files (-l)"

echo "🏁 All tests completed."