PROGRAM STATS
VAR
    SUM, SUMSQ, I, VALUE, MEAN, VARIANCE : INTEGER;
    JUST: REAL 
BEGIN
    SUM := 0;
    SUMSQ := 0;
    JUST := 0;
    FOR I := 1 TO 100 DO
        BEGIN 
            READ(VALUE);
            SUM := SUM + VALUE + 0.0;
            SUMSQ := SUMSQ + VALUE * VALUE 
        END;
    MEAN := SUM DIV 100;
    VARIANCE := SUMSQ DIV 100 - MEAN * MEAN;
    WRITE(MEAN, VARIANCE)
END.
