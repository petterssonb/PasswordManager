# PasswordManager

OBS!! Makefile som finns med i programmet går bara att köra på mac.

Commits sker i main branchen.

Programmet är uppdelat i en h fil och cpp fil.

I filen users.txt finns de säkra kontouppgifterna = username:salt:hashedAndSaltedPasswords
I filen hashes.txt finns de osäkra kontouppgifterna som man kan knäcka, lagrat = username:hashedPassword

Filer med vanliga lösenord är 100kMostUsedPasswords.txt och example.txt

I filen 100kMostUsedPasswords.txt är alla lösenord genererade att lägga till antingen 2024 eller 123, samt
ett special tecken i lösenord som inte redan har det i dom. Jag valde att ha 2024 som är det nuvarande året
och 123 för det har jag själv använt mest när jag skapat lösenord, samt att ! och ? är de ända tecken jag
har använt när ett lösenord ber om specialtecken.

Programmet körs genom Makefile
