@echo off
echo ===== Checking DevOps tools on this PC =====
echo.
echo --- Git ---
git --version 2>nul || echo   NOT INSTALLED
echo.
echo --- Java ---
java -version 2>&1 | findstr /i "version" || echo   NOT INSTALLED
echo.
echo --- javac ---
javac -version 2>nul || echo   NOT INSTALLED
echo.
echo --- Maven ---
call mvn -version 2>nul | findstr /i "Apache Maven" || echo   NOT INSTALLED
echo.
echo --- Docker ---
docker --version 2>nul || echo   NOT INSTALLED
echo.
echo --- kubectl ---
kubectl version --client 2>nul || echo   NOT INSTALLED
echo.
echo --- Python ---
python --version 2>nul || echo   NOT INSTALLED
echo.
echo --- gcc (for Exp 2 C programs, optional) ---
gcc --version 2>nul | findstr /i "gcc" || echo   NOT INSTALLED
echo.
echo ===== Done =====
pause
