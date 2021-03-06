Benas Budrys 5 gr. 2022

## 5. VIP bankas (ADT: eilė, prioritetinė eilė).

> Procesas 1: klientai ateina į banką ir kreipiasi į bet kurį laisvą kasininką, jei visi kasininkai užsiėmę, klientai stoja į bendrą eilę, tačiau yra VIP klientai, kurie aptarnaujami be eilės, žinoma, jei visi kasininkai užimti VIP klientas irgi turi laukti, netgi gali susidaryti VIP eilė.

> Procesas 2: bankas turi atskirus kasininkus, kurie dirba su paprastais ir VIP klientais.

> Pradiniai duomenys: paprasto ir VIP kliento atėjimo tikimybės, paprastus ir VIP klientus aptarnaujančių kasininkų skaičius, paprasto ir VIP kliento aptarnavimo laikas, darbo dienos ilgis.

> Įvertinti, kuris procesas tikslingesnis bankui. Vertinama, pavyzdžiui, pagal tokį kriterijų: suminis kasininkų prastovų laikas, dvigubas suminis kasininkų viršvalandžių laikas (visi klientai, kurie atėjo į banką iki darbo pabaigos, turi būti aptarnauti), trigubas vidutinis paprasto kliento laukimo laikas, dešimtgubas VIP kliento maksimalaus laukimo laikas.

---

Notes about input:

- `customerChance` - in integer %
- `serviceTime` - in integer time units
- `bankWorkingTime` - in integer time units

Score calculation:

Overall process score = `cashierDowntime + 2 * cashierOvertime + 5 * averageBasicCustomerWaitingTime + 10 * averageVIPCustomerWaitingTime`
