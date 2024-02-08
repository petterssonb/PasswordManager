# PasswordManager

OBS!! Makefile som finns med i programmet går bara att köra på mac.

Commits sker i main branchen.

Programmet är uppdelat i en h fil och cpp fil.

I filen users.txt finns de säkra kontouppgifterna = username:salt:hashedAndSaltedPasswords
I filen hashes.txt finns de osäkra kontouppgifterna som man kan knäcka, lagrat = username:hashedPassword

Filer med vanliga lösenord är 100kMostUsedPasswords.txt och example.txt

I filen 100kMostUsedPasswords.txt längst ner finns kryddningen med mera "patterns" såsom sommar2024 osv.

Programmet körs genom Makefile
