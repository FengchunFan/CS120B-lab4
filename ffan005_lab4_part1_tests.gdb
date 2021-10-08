echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x01, 0x01, 0x01, 0x01 => PORTB: 0x01, state: onPress"
set state = start
setPINA 0x01
continue 2
setPINA 0x01
continue 2 
setPINA 0x01
continue 2
setPINA 0x01
continue 2
expectPORTB 0x01
expect state onPress
checkResult

test "PINA: 0x01 => PORTB: 0x02, state: onRelease"
set state = start
setPINA 0x01
continue 2
expectPORTB 0x02
expect state onRelease
checkResult

test "PINA: 0x01, 0x01 => PORTB: 0x01, state: offPress"
set state = start
setPINA 0x01
continue 2
setPINA 0x01
continue 2 
expectPORTB 0x01
expect state offPress
checkResult

# Add tests below

# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
