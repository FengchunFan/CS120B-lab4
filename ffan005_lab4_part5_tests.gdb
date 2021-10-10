echo ======================================================\n
echo Running all tests..."\n\n

# Example test:
test "PINA: 0x00 => PORTB: 0x00, state: Check"
set state = Start
setPINA 0x00
continue 2
expectPORTB 0x07
expect state Check
checkResult

test "PINA: 0x00, PINA: 0x04 => PORTB: 0x00, state: Step1"
set state = Start
setPINA 0x00
continue 2
setPINA 0x04
continue 2
expectPORTB 0x00
expect state Step1
checkResult

test "PINA: 0x00, PINA: 0x04, PINA: 0x04 => PORTB: 0x00, state: Step2"
set state = Start
setPINA 0x00
continue 2
setPINA 0x04
continue 2
setPINA 0x04
continue 2
expectPORTB 0x00
expect state Step2
checkResult

test "PINA: 0x00, PINA: 0x04, PINA: 0x04, 0x02 => PORTB: 0x00, state: Unlock"
set state = Start
setPINA 0x00
continue 2
setPINA 0x04
continue 2
setPINA 0x04
continue 2
setPINA 0x02
continue 2
expectPORTB 0x01
expect state Unlock
checkResult

test "PINA: 0x00, PINA: 0x04, PINA: 0x04, 0x02, 0x80 => PORTB: 0x00, state: Locked"
set state = Start
setPINA 0x00
continue 2
setPINA 0x04
continue 2
setPINA 0x04
continue 2
setPINA 0x02
continue 2
setPINA 0x80
continue 2
expectPORTB 0x00
expect state Locked
checkResult
# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
