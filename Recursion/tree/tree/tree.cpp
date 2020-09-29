//
//  main.cpp
//  tree
//
//  Created by Mitchell McLinton on 7/2/20.
//  Copyright © 2020 Mitchell McLinton. All rights reserved.
//

#include <iostream>
#include <cassert>

/* TODO: REMOVE ALL ABOVE */


  // Return the number of ways that all n2 elements of a2 appear
  // in the n1 element array a1 in the same order (though not
  // necessarily consecutively).  The empty sequence appears in a
  // sequence of length n1 in 1 way, even if n1 is 0.
  // For example, if a1 is the 7 element array
  //    10 50 40 20 50 40 30
  // then for this value of a2     the function must return
  //    10 20 40            1
  //    10 40 30            2
  //    20 10 40            0
  //    50 40 30            3
int countContains(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return 1;
    else if (n1 < n2)
        return 0;
    
    int count = 0;
    if (a1[0] == a2[0])
        count += countContains(a1+1, n1-1, a2+1, n2-1);
    
    count += countContains(a1+1, n1-1, a2, n2);
    
    return count;
}

  // Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}

  // Rearrange the elements of the array so that all the elements
  // whose value is > separator come before all the other elements,
  // and all the elements whose value is < separator come after all
  // the other elements.  Upon return, firstNotGreater is set to the
  // index of the first element in the rearranged array that is
  // <= separator, or n if there is no such element, and firstLess is
  // set to the index of the first element that is < separator, or n
  // if there is no such element.
  // In other words, upon return from the function, the array is a
  // permutation of its original value such that
  //   * for 0 <= i < firstNotGreater, a[i] > separator
  //   * for firstNotGreater <= i < firstLess, a[i] == separator
  //   * for firstLess <= i < n, a[i] < separator
  // All the elements > separator end up in no particular order.
  // All the elements < separator end up in no particular order.
void separate(double a[], int n, double separator,
                    int& firstNotGreater, int& firstLess)
{
    if (n < 0)
    n = 0;

      // It will always be the case that just before evaluating the loop
      // condition:
      //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
      //  Every element earlier than position firstNotGreater is > separator
      //  Every element from position firstNotGreater to firstUnknown-1 is
      //    == separator
      //  Every element from firstUnknown to firstLess-1 is not known yet
      //  Every element at position firstLess or later is < separator

    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}

  // Rearrange the elements of the array so that
  // a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
  // If n <= 1, do nothing.
void order(double a[], int n)
{
    if (n <= 1)
        return;
    int firstNotGreater = 0;
    int firstLess = n;
    
    separate(a, n, a[0], firstNotGreater, firstLess);
    order(a, firstNotGreater);
    order(a+firstLess, n-firstLess);
}

/* TODO: REMOVE ALL BELOW */

int main() {
    double a10[10] = { 10, 30, 50, 90, 30, 40, 50, 10, 30, 50 };
    double a11[3] = { 10, 30, 50 };
    assert(countContains(a10, 10, a11, 3) == 7);
    double a12[1] = { 10 };
    assert(countContains(a10, 10, a12, 1) == 2);
    assert(countContains(a10, 10, a10, 10) == 1);
    assert(countContains(a10, -3, a11, -5) == 1);
    assert(countContains(a10, 5, a11, -5) == 1);
    assert(countContains(a10, -3, a11, 3) == 0);
    double a13[2] = { 30, 50 };
    assert(countContains(a10, 10, a13, 2) == 6);
    double yeet = 40;
    double* a14 = &yeet;
    assert(countContains(a10, 10, a14, 1) == 1);
    
    double big1[512] = { 1673703, 1406323, 81689, -217381, -463444, -892759, 2114850, 2144430, -508017, -1368504, -1148508, 1352373, -667244, -653145, 1908269, 1970534, 151796, -1494011, -92967, 1594262, 1290865, 964614, 1595771, 724963, 19141, 1557453, -599713, -1384892, 650562, 16893, -1567797, -1482554, 1883429, 111213, -1971965, -1533184, -1361567, 1633238, -1095778, 948185, -1681888, -1960282, -1105585, -796586, -25424, 472082, -595856, -50163, 875816, 231319, 1861622, -1129005, -1462214, -1381487, -1407628, -492744, 1747245, -632290, 1272735, -1616974, 2034532, 879293, 231893, -4943, 666335, 2093650, -957633, 594309, 709249, -1654563, 1886515, 179639, 686679, -1928003, -32471, -591952, -134758, 699598, -1426597, -287109, -1032664, -298904, 1829982, -2089991, -2089111, -1054534, 2045216, -802562, -564410, -562785, -1417097, 1407972, 1984607, -1871967, 728575, 7080, -1430045, -1699680, 1329490, -1014947, 1846145, -1228597, -163856, 1677175, -683388, -1914888, 1240598, -119542, 2111754, -616022, -756368, 692650, -809970, 137470, 539641, -1391745, 1890848, 793420, -1431135, 603463, 9580, -498104, 164174, -1257964, -80320, -2121486, 2145261, 1586891, -129802, 1906684, 1090501, 1794139, -1422223, 2006061, 1615508, -1302817, 919636, -305894, -1174262, -698059, 1375314, 1603660, 1299957, 153804, -217433, -537754, -46216, 1729365, 175531, 592674, 585921, 2121161, 875643, -2095383, 411461, -1924102, 310754, 1830236, -1687373, -1653710, 2014606, -601404, -336725, -1450784, -1872942, 1746976, 192748, -658447, -1332787, -2064239, -2045780, -792514, -1978156, -1015174, 1978856, 1556390, -1151873, -1003794, 1307457, 1284188, 1312562, 330504, 37988, 1297029, 1015488, 1163864, -214581, -1364844, 1209367, 298309, -269655, -833540, -658421, 1828126, 905353, -1312000, -290396, -970290, 1034033, -264947, -935174, -1955586, -838192, -2112044, -951265, 1080077, 1087052, 540148, -1863995, -1843495, -2078493, -779977, -1865273, 715814, 1704130, -258226, 1099830, 1699514, -170742, 2002412, 1354472, -534917, -254707, -509628, -206251, 933537, 270749, 988854, -1186736, -1178561, -436134, -1151838, 1746253, -766365, -1178123, 93311, -665194, -2073266, -518716, -1568548, -649773, 2020183, -1175476, 697122, 987148, -238546, 538426, 1176527, 776435, -313743, 1645629, -1587503, -1439317, 791280, -17243, -1443186, -80730, -1341150, 959190, -1143115, -1123307, 73354, -947401, 1435806, -731361, 839138, -84507, -1237576, 202837, 62593, -638394, 1336537, -408894, -94162, 115727, 1801040, -1432204, -1519612, 1732916, 1283160, -1341196, 1231791, -1987934, 1439174, 208823, -1850030, 1982893, 836077, 1192255, -1557029, -1116872, 1069365, 1839302, -1395573, -1240562, 333818, 113820, 2031820, -1534725, 304782, 1151100, -329109, 231548, -1394775, 2071191, 179010, 175202, 279050, 1746356, -590908, 1359986, -131865, -366689, -370750, 1384361, 984092, 519317, 2092508, -1285004, 918352, 565691, -1262586, 590012, -260261, -1280815, 963475, 1721339, 1342167, -1626035, 1032688, -1355392, -1121932, 774186, 290991, 837012, 1272185, 1552427, -250017, 1883297, 114572, 269196, -1187381, -211526, -2004595, 1708283, -1428189, 1235522, 1201573, -1585735, 817393, 2032034, -820110, -1259142, -910957, 2016916, -1807691, 318291, 1243119, 1361973, -786555, 1380413, 648548, 1024876, -2004540, -761119, 1046291, 1334763, 1309827, -1578800, 215238, -2068158, -433346, -1676036, -1004834, -693829, 425338, -2082504, -1983284, 1553788, -723216, 383765, 585797, 1516285, 1164372, 556446, 795374, -1599760, 782932, 1963940, -991477, -1365709, -1752771, -1477342, 835891, 492907, -151871, -1141720, -1040966, 2049405, 233353, 1571802, 812266, -380912, 651902, -1352244, -1203803, -1600149, -556376, 1893962, 1715728, 1005458, 1794318, 2049828, -678024, 1882547, 1607340, 1935747, 1207482, -1415423, -1831275, 1527460, 840780, -693948, -67532, 539970, 1886172, 113559, 1543508, 190723, 521161, 174438, 670034, 1976346, -31620, 1260510, 1720521, -1048876, -1630775, 403599, -1532111, 1325764, 236633, 500920, 698065, -1023206, 1421391, -585554, -1155250, 1526003, -2104616, 1605123, 366218, 1485198, -1163887, 786316, 2030930, -1168370, -216593, -1440325, 701697, 28844, -1578030, 1584335, 1751153, 471535, -1014903, -78403, -414106, 1017048, -1882649, -866504, 1379964, 983821, 1341934, -567372, 950019, 27052, 1887632, 993643, -769342, 1172108, 952180, -8796, -1245893, 1281528, -463705, -1649599, -1080236, -29340, -157723, 675238, -1506256, -1275617, -1497283, 647007, -1189923, -1332874, -475776, 752279, 1668316, -1102717, 1278149, -2013509, -2033724, -1531730, 802112, 213866, -1235535, 860161, 978598, 2074624, 22044 };
    
    double orderedBig1[515] = { 2145261, 2144430, 2121161, 2114850, 2111754, 2093650, 2092508, 2074624, 2071191, 2049828, 2049405, 2045216, 2034532, 2032034, 2031820, 2030930, 2020183, 2016916, 2014606, 2006061, 2002412, 1984607, 1982893, 1978856, 1976346, 1970534, 1963940, 1935747, 1908269, 1906684, 1893962, 1890848, 1887632, 1886515, 1886172, 1883429, 1883297, 1882547, 1861622, 1846145, 1839302, 1830236, 1829982, 1828126, 1801040, 1794318, 1794139, 1751153, 1747245, 1746976, 1746356, 1746253, 1732916, 1729365, 1721339, 1720521, 1715728, 1708283, 1704130, 1699514, 1677175, 1673703, 1668316, 1645629, 1633238, 1615508, 1607340, 1605123, 1603660, 1595771, 1594262, 1586891, 1584335, 1571802, 1557453, 1556390, 1553788, 1552427, 1543508, 1527460, 1526003, 1516285, 1485198, 1439174, 1435806, 1421391, 1407972, 1406323, 1384361, 1380413, 1379964, 1375314, 1361973, 1359986, 1354472, 1352373, 1342167, 1341934, 1336537, 1334763, 1329490, 1325764, 1312562, 1309827, 1307457, 1299957, 1297029, 1290865, 1284188, 1283160, 1281528, 1278149, 1272735, 1272185, 1260510, 1243119, 1240598, 1235522, 1231791, 1209367, 1207482, 1201573, 1192255, 1176527, 1172108, 1164372, 1163864, 1151100, 1099830, 1090501, 1087052, 1080077, 1069365, 1046291, 1034033, 1032688, 1024876, 1017048, 1015488, 1005458, 993643, 988854, 987148, 984092, 983821, 978598, 964614, 963475, 959190, 952180, 950019, 948185, 933537, 919636, 918352, 905353, 879293, 875816, 875643, 860161, 840780, 839138, 837012, 836077, 835891, 817393, 812266, 802112, 795374, 793420, 791280, 786316, 782932, 776435, 774186, 752279, 728575, 724963, 715814, 709249, 701697, 699598, 698065, 697122, 692650, 686679, 675238, 670034, 666335, 651902, 650562, 648548, 647007, 603463, 594309, 592674, 590012, 585921, 585797, 565691, 556446, 540148, 539970, 539641, 538426, 521161, 519317, 500920, 492907, 472082, 471535, 425338, 411461, 403599, 383765, 366218, 333818, 330504, 318291, 310754, 304782, 298309, 290991, 279050, 270749, 269196, 236633, 233353, 231893, 231548, 231319, 215238, 213866, 208823, 202837, 192748, 190723, 179639, 179010, 175531, 175202, 174438, 164174, 153804, 151796, 137470, 115727, 114572, 113820, 113559, 111213, 93311, 81689, 73354, 62593, 37988, 28844, 27052, 22044, 19141, 16893, 9580, 7080, -4943, -8796, -17243, -25424, -29340, -31620, -32471, -46216, -50163, -67532, -78403, -80320, -80730, -84507, -92967, -94162, -119542, -129802, -131865, -134758, -151871, -157723, -163856, -170742, -206251, -211526, -214581, -216593, -217381, -217433, -238546, -250017, -254707, -258226, -260261, -264947, -269655, -287109, -290396, -298904, -305894, -313743, -329109, -336725, -366689, -370750, -380912, -408894, -414106, -433346, -436134, -463444, -463705, -475776, -492744, -498104, -508017, -509628, -518716, -534917, -537754, -556376, -562785, -564410, -567372, -585554, -590908, -591952, -595856, -599713, -601404, -616022, -632290, -638394, -649773, -653145, -658421, -658447, -665194, -667244, -678024, -683388, -693829, -693948, -698059, -723216, -731361, -756368, -761119, -766365, -769342, -779977, -786555, -792514, -796586, -802562, -809970, -820110, -833540, -838192, -866504, -892759, -910957, -935174, -947401, -951265, -957633, -970290, -991477, -1003794, -1004834, -1014903, -1014947, -1015174, -1023206, -1032664, -1040966, -1048876, -1054534, -1080236, -1095778, -1102717, -1105585, -1116872, -1121932, -1123307, -1129005, -1141720, -1143115, -1148508, -1151838, -1151873, -1155250, -1163887, -1168370, -1174262, -1175476, -1178123, -1178561, -1186736, -1187381, -1189923, -1203803, -1228597, -1235535, -1237576, -1240562, -1245893, -1257964, -1259142, -1262586, -1275617, -1280815, -1285004, -1302817, -1312000, -1332787, -1332874, -1341150, -1341196, -1352244, -1355392, -1361567, -1364844, -1365709, -1368504, -1381487, -1384892, -1391745, -1394775, -1395573, -1407628, -1415423, -1417097, -1422223, -1426597, -1428189, -1430045, -1431135, -1432204, -1439317, -1440325, -1443186, -1450784, -1462214, -1477342, -1482554, -1494011, -1497283, -1506256, -1519612, -1531730, -1532111, -1533184, -1534725, -1557029, -1567797, -1568548, -1578030, -1578800, -1585735, -1587503, -1599760, -1600149, -1616974, -1626035, -1630775, -1649599, -1653710, -1654563, -1676036, -1681888, -1687373, -1699680, -1752771, -1807691, -1831275, -1843495, -1850030, -1863995, -1865273, -1871967, -1872942, -1882649, -1914888, -1924102, -1928003, -1955586, -1960282, -1971965, -1978156, -1983284, -1987934, -2004540, -2004595, -2013509, -2033724, -2045780, -2064239, -2068158, -2073266, -2078493, -2082504, -2089111, -2089991, -2095383, -2104616, -2112044, -2121486 };
    
    double big2[512] = { -773127, -1306867, -1114607, 1192511, -2026078, -2033411, 1134067, 1145155, -10808, 1634881, -1799359, 1510381, -1200935, 391953, -128335, -2044397, 1659845, -1442152, -1339704, -1121620, 639082, 1186213, -1147355, 317576, 615249, -280072, -1356789, -1310171, 1887416, 1734144, -1174557, 957203, 1474870, 1150018, -1638176, 354137, -1690742, 875256, -900067, -1705893, -2101789, 1573862, 1824474, -1723962, 568684, 1149497, 1107077, -1640738, -1729578, 2099384, -1980341, -1072538, -675744, -223700, -156262, 1811055, -1365337, 1671109, -1119059, 1818859, -2123604, 2118528, -334243, -189244, -1034657, -941450, -662795, 553684, -1408642, -1607463, 27656, 1070840, -926197, 1516342, -1077666, 299985, 165436, -1967259, -789764, -1432283, -215806, 912099, -1890816, -1029121, -17303, -978914, -1158472, -966156, 1503956, -516045, -1543020, 371747, 272979, -1208723, 799248, 115628, -1486944, -77221, -1365076, -141549, -2066688, 1711508, -1629874, -1441041, 357838, 1370389, -762269, -402259, -1171789, -1864345, 546416, -1880318, -1408157, -2032932, -841924, 700348, -833539, -327943, -2082322, 1694476, 1571979, -570003, 815852, 1471544, -821285, -1650557, 495975, -747011, -1111252, -2049884, 1810140, -2100542, 1282439, -59489, -1116929, 423553, 468495, 2144539, -889555, 1689608, 381980, -750409, -2112103, -1107807, 293711, -1478956, 255353, -1900918, -1028064, 885812, -15908, -352742, -1735991, 1944100, -1254089, 1715479, 1246929, 1752237, 169278, 136352, -1992776, -2120636, 143158, -22630, -211240, -1261608, 1893067, -1747570, 1578539, 310374, -1260451, 1630902, 464457, -1391674, -858283, 937347, 428600, 1579491, 483220, -43640, -1557011, -1171621, -400457, -657858, -425761, 1783397, 805696, -1278701, 881691, -367822, -1739348, -52991, 1327952, 1856062, -843953, 1261299, -1243770, 1059218, -2039566, 1578741, -1412492, 1202348, 449980, 739949, 1144948, 1296310, 1671719, 1782444, 1339802, 890668, 1012088, 1316669, 79228, 1756573, -1345168, -233758, -1670743, -814217, -1574235, 2084807, -1849898, -679234, 312015, -98937, 1472215, -1034838, 1959948, 694478, -938434, 73138, -765592, 606662, -961667, -1722042, 1361678, -674447, -718711, -1513144, 1433243, 1952953, 147241, -602908, -1199279, 1810052, 1449560, -807579, -1243035, -153502, -143336, 1099612, 138730, -925114, 2084542, 75343, 1566015, 419016, 1998541, 1722863, 1694718, -101350, 1555565, 570275, 2110945, -657564, 1203944, -1618491, 1664923, 1681411, -953381, 497820, 482000, 484413, -692436, 385136, 726062, -1300153, 116581, 1802489, -1928341, 117284, -1022923, 2026796, 327871, -43179, -568351, 9273, 799113, -1358406, -766791, 1652227, 119639, 7629, -75856, -573748, 996765, -2027827, 1361696, 1326678, -1614979, 785567, -104847, 336814, -386636, 103129, 1195385, 331896, -273362, -1438989, 1134059, -1352804, -426238, -1560006, 191240, 523814, -378236, 1163296, 482680, -1371756, 855393, 586848, -1723143, 1694664, 703615, -1666620, -1737710, -48061, -110797, 1295169, 1848964, -1378472, -1013408, -366098, -883386, -978193, 1789511, -1045035, -795828, -1075931, -1520835, 453488, 124670, -796260, 538285, -1786259, -2088741, 1075166, -131171, 1820375, 929071, -886557, -1355064, 1662821, -406846, 692753, 315002, -1637628, 2114108, -1949036, -987966, 1838069, -290904, 1456262, 1472153, 1377319, 158712, -200819, -2069813, -216488, -2025399, -1812123, 550753, 1267780, 1169163, 248426, -706969, -1100312, 976990, 329730, -1615931, 977368, 408088, -1306492, -1748456, -1011281, 117903, 1971756, 543357, -1329835, -1455384, 608918, -631214, -1925636, -1931918, -1542375, 1475596, 903996, -1616733, 2120977, 676309, 543565, -1855354, 670328, 160071, -474041, -706898, 929769, 48743, -1326688, -25279, -1329052, 327155, 346386, 999177, -1405609, 2017085, -1929923, 79393, -26894, 1607589, -1394333, 1426283, -583520, -1938426, -1767429, 1793024, -647735, -1600612, -2106495, -495696, 538328, 1547975, 1421248, 2007190, 979375, 246796, 1496513, 742602, 1566954, -203321, 60106, -632822, 42620, -243775, -1515596, -572346, -315525, -185795, -1235190, 397984, 75221, -573516, 1855380, -1829520, 844177, 1670993, 1616645, -960801, 1458843, 113826, 746478, 1574064, -504648, -1101564, -766874, -562410, -1683674, 868931, 746282, 1915202, 1697303, 1826930, -6588, 1742113, 336526, 2127442, 1739272, -1184324, -752232, -820145, -1127755, 237865, 1517308, -1520513, 13863, 1953602, -1633958, -1734989, -1665178, -259006, 1531474, 517110, 1666345, 1545458, -1929568, 1895254, 1425882, 590453, 1533790, 353426, -1159720, -793683, 1201771, 1977415, 1428546, -2065512, -1922572, -1339801, -669050, 243605, -490452, 1222323, -743307 };
    
    double orderedBig2[512] = { 2144539, 2127442, 2120977, 2118528, 2114108, 2110945, 2099384, 2084807, 2084542, 2026796, 2017085, 2007190, 1998541, 1977415, 1971756, 1959948, 1953602, 1952953, 1944100, 1915202, 1895254, 1893067, 1887416, 1856062, 1855380, 1848964, 1838069, 1826930, 1824474, 1820375, 1818859, 1811055, 1810140, 1810052, 1802489, 1793024, 1789511, 1783397, 1782444, 1756573, 1752237, 1742113, 1739272, 1734144, 1722863, 1715479, 1711508, 1697303, 1694718, 1694664, 1694476, 1689608, 1681411, 1671719, 1671109, 1670993, 1666345, 1664923, 1662821, 1659845, 1652227, 1634881, 1630902, 1616645, 1607589, 1579491, 1578741, 1578539, 1574064, 1573862, 1571979, 1566954, 1566015, 1555565, 1547975, 1545458, 1533790, 1531474, 1517308, 1516342, 1510381, 1503956, 1496513, 1475596, 1474870, 1472215, 1472153, 1471544, 1458843, 1456262, 1449560, 1433243, 1428546, 1426283, 1425882, 1421248, 1377319, 1370389, 1361696, 1361678, 1339802, 1327952, 1326678, 1316669, 1296310, 1295169, 1282439, 1267780, 1261299, 1246929, 1222323, 1203944, 1202348, 1201771, 1195385, 1192511, 1186213, 1169163, 1163296, 1150018, 1149497, 1145155, 1144948, 1134067, 1134059, 1107077, 1099612, 1075166, 1070840, 1059218, 1012088, 999177, 996765, 979375, 977368, 976990, 957203, 937347, 929769, 929071, 912099, 903996, 890668, 885812, 881691, 875256, 868931, 855393, 844177, 815852, 805696, 799248, 799113, 785567, 746478, 746282, 742602, 739949, 726062, 703615, 700348, 694478, 692753, 676309, 670328, 639082, 615249, 608918, 606662, 590453, 586848, 570275, 568684, 553684, 550753, 546416, 543565, 543357, 538328, 538285, 523814, 517110, 497820, 495975, 484413, 483220, 482680, 482000, 468495, 464457, 453488, 449980, 428600, 423553, 419016, 408088, 397984, 391953, 385136, 381980, 371747, 357838, 354137, 353426, 346386, 336814, 336526, 331896, 329730, 327871, 327155, 317576, 315002, 312015, 310374, 299985, 293711, 272979, 255353, 248426, 246796, 243605, 237865, 191240, 169278, 165436, 160071, 158712, 147241, 143158, 138730, 136352, 124670, 119639, 117903, 117284, 116581, 115628, 113826, 103129, 79393, 79228, 75343, 75221, 73138, 60106, 48743, 42620, 27656, 13863, 9273, 7629, -6588, -10808, -15908, -17303, -22630, -25279, -26894, -43179, -43640, -48061, -52991, -59489, -75856, -77221, -98937, -101350, -104847, -110797, -128335, -131171, -141549, -143336, -153502, -156262, -185795, -189244, -200819, -203321, -211240, -215806, -216488, -223700, -233758, -243775, -259006, -273362, -280072, -290904, -315525, -327943, -334243, -352742, -366098, -367822, -378236, -386636, -400457, -402259, -406846, -425761, -426238, -474041, -490452, -495696, -504648, -516045, -562410, -568351, -570003, -572346, -573516, -573748, -583520, -602908, -631214, -632822, -647735, -657564, -657858, -662795, -669050, -674447, -675744, -679234, -692436, -706898, -706969, -718711, -743307, -747011, -750409, -752232, -762269, -765592, -766791, -766874, -773127, -789764, -793683, -795828, -796260, -807579, -814217, -820145, -821285, -833539, -841924, -843953, -858283, -883386, -886557, -889555, -900067, -925114, -926197, -938434, -941450, -953381, -960801, -961667, -966156, -978193, -978914, -987966, -1011281, -1013408, -1022923, -1028064, -1029121, -1034657, -1034838, -1045035, -1072538, -1075931, -1077666, -1100312, -1101564, -1107807, -1111252, -1114607, -1116929, -1119059, -1121620, -1127755, -1147355, -1158472, -1159720, -1171621, -1171789, -1174557, -1184324, -1199279, -1200935, -1208723, -1235190, -1243035, -1243770, -1254089, -1260451, -1261608, -1278701, -1300153, -1306492, -1306867, -1310171, -1326688, -1329052, -1329835, -1339704, -1339801, -1345168, -1352804, -1355064, -1356789, -1358406, -1365076, -1365337, -1371756, -1378472, -1391674, -1394333, -1405609, -1408157, -1408642, -1412492, -1432283, -1438989, -1441041, -1442152, -1455384, -1478956, -1486944, -1513144, -1515596, -1520513, -1520835, -1542375, -1543020, -1557011, -1560006, -1574235, -1600612, -1607463, -1614979, -1615931, -1616733, -1618491, -1629874, -1633958, -1637628, -1638176, -1640738, -1650557, -1665178, -1666620, -1670743, -1683674, -1690742, -1705893, -1722042, -1723143, -1723962, -1729578, -1734989, -1735991, -1737710, -1739348, -1747570, -1748456, -1767429, -1786259, -1799359, -1812123, -1829520, -1849898, -1855354, -1864345, -1880318, -1890816, -1900918, -1922572, -1925636, -1928341, -1929568, -1929923, -1931918, -1938426, -1949036, -1967259, -1980341, -1992776, -2025399, -2026078, -2027827, -2032932, -2033411, -2039566, -2044397, -2049884, -2065512, -2066688, -2069813, -2082322, -2088741, -2100542, -2101789, -2106495, -2112103, -2120636, -2123604 };
    
    double big3[512] = { 141646, -1890890, 331393, -2112773, 1783126, -1307768, 1314313, 1455524, -667418, 416022, 35143, 841132, 1698949, -430931, 667370, -1348857, -922992, -2090559, 580722, 851452, -2095927, 1876946, -516083, 142529, 1965008, -665709, -11864, 726114, -863892, -1326135, -199095, -1455961, -1459616, 1550962, 1592053, -304909, -1064481, 766127, 1023694, 1617808, -993168, 467857, 1888437, 377571, -103361, -1516588, 1173776, -970154, 1655108, 537595, -117818, -1098722, -1981226, 1980844, 311222, -186281, -1533701, -1652624, 648524, -1108149, 1609842, -1457328, 20399, 282250, -425556, 829845, -1415261, 1749595, -1370170, 51886, 383619, 2096539, 2059272, 327425, -1161902, 614897, 589869, -1273565, -1026086, 248992, -2110456, 487603, 1561579, -1107070, -375023, 2096662, 95159, -777436, 330240, -923733, -13085, 1281622, -1888362, 682046, 264990, 861067, 512931, -2142423, 443333, 1178400, 2059389, 860747, -461692, -1061430, 1746476, -79719, -1984581, 1107268, -1129425, -1120642, -318869, 811215, 1822812, 468370, 1023513, 1969184, 59654, -569214, -2130715, 1254861, 155480, 378438, -424253, 277419, 1083432, -2073827, -1390105, -1761996, -200213, -738950, 887611, -984309, 1445961, 636521, -1689948, 1955799, -616117, 746259, -686857, -181143, 1822608, 1851470, 671107, 848450, -41035, 1909065, -1109657, -1882908, -2125642, 828449, 1901996, -131440, -1186410, -1167801, 291610, -991459, -199341, -1233287, -292458, -81733, 1329300, -1674507, 1557711, 2035833, -1479076, -1251037, 1643566, 1004733, -1794904, 1798822, -1321600, 82486, 70770, 2096547, 2118761, -477006, 1294188, 1829056, -1272573, 889863, 382541, 1394931, 1710754, -1552263, -305120, 74131, 1486025, 45867, -595600, 1824012, -1811287, 852681, -198053, 2048256, 1560831, -1581629, -1274407, 1827879, -675002, 2147269, 1478067, -1232700, 1171823, -1381131, 1835678, -633484, -348517, -1540846, 449600, 221228, 458149, -2065210, -2100651, -107736, -1141285, 892774, -1222643, 974909, 979729, -1056533, 900176, 1781454, 928913, -1451028, 1706897, 765849, -1173829, -1045224, -1820561, 1209206, -645549, -219824, -2021387, 1038450, -466377, -1763115, 1497860, -892134, 1819584, -38911, -1878630, 1943692, 1807935, 792333, -26621, 1000776, -188098, 1390298, -1809421, -1913826, -372017, -416154, -295103, 1867394, -66431, -1049194, 28669, -1836399, -1675462, 1620469, -1140128, -1102433, -759558, 2054310, 621422, -1167470, -524425, 944603, -1947029, -1297343, 1737200, -1159129, -994650, 2089185, -1227877, -16956, 2674, -2082403, -1833962, -2129045, -1679628, 155796, -2105786, -635022, 462738, 1234678, -1143816, -965415, 1822702, -2034441, 2037977, 39165, 216755, 954440, 102381, 258206, -1612291, 65114, -338894, -1857584, 1426434, -1539592, 482682, -33077, 101042, -77698, 363731, 639616, -452892, -513959, -153760, -870933, -1385686, -1732035, 467183, -838343, 1171767, 454601, -1733661, -445346, -1011891, 970879, -187104, 722765, 1369861, -783662, -1075704, -1561773, 1933973, 449703, -1670107, 620885, 1648067, -1442614, 701106, -378032, -466677, -824319, -1986593, 501342, 1769876, -2071814, -109863, 627666, -1406355, 1085492, -1406918, -555315, 1996218, 858878, -122430, 798676, 1935315, 1261826, -2019712, -592066, 1333670, -1193362, 1359139, 809449, 998996, 484130, -1494795, -458945, -543976, 1736627, 562892, -748882, 1466309, -1225736, -54813, -2086770, -378170, 709641, -1809626, -1086588, 299242, 2034471, -293994, -1663842, 1349413, -1208318, -929079, -643492, 553848, -623392, -1326026, 552912, -1825587, -1055314, -1214283, -881955, -800874, -1167277, -174151, -557940, 1596629, 1185911, 689366, -1190349, -577973, 750883, -1767253, -788646, -339540, 1186479, -1254774, 1639155, 545671, -1040503, 1166649, -1948211, 1156357, 1739056, -194877, -1064919, 1730992, -104953, -170183, -1383393, -894878, -1208873, 285675, -276453, -1301552, 1134412, 1025310, -671539, -826553, -325393, 470347, -769527, -71682, 2016364, -873994, -2045859, -1425278, 584554, 1162289, 1326682, -2131778, -808195, 960059, 2012751, 381500, 332759, 2041080, 888983, -1590490, 721732, -1923648, -34249, 1871854, 1664819, -1574638, -1366226, -696949, 34706, -1109295, -225572, -684334, -1114613, 1959304, -1655463, 1513249, 1672811, -963416, -730827, 907747, 523537, 1411361, -106642, 995781, 413356, 792382, -935990, 1010680, -1603901, 1791370, -672292, 263850, -1361655, -1833499, 1825818, -1702380, 1381010, -34638, 2138741, 628660, -1066760, -1718453, 1861592, -456297, -1960202, 896486, 1332592, 755850, -105632, 611735, -1385775, -1577078, -809932, 61658, 1242337, -127360, 591399, 1929844, -1517892, 1865366, 1947117, 1112940, 164227 };
    
    double orderedBig3[512] = { 2147269, 2138741, 2118761, 2096662, 2096547, 2096539, 2089185, 2059389, 2059272, 2054310, 2048256, 2041080, 2037977, 2035833, 2034471, 2016364, 2012751, 1996218, 1980844, 1969184, 1965008, 1959304, 1955799, 1947117, 1943692, 1935315, 1933973, 1929844, 1909065, 1901996, 1888437, 1876946, 1871854, 1867394, 1865366, 1861592, 1851470, 1835678, 1829056, 1827879, 1825818, 1824012, 1822812, 1822702, 1822608, 1819584, 1807935, 1798822, 1791370, 1783126, 1781454, 1769876, 1749595, 1746476, 1739056, 1737200, 1736627, 1730992, 1710754, 1706897, 1698949, 1672811, 1664819, 1655108, 1648067, 1643566, 1639155, 1620469, 1617808, 1609842, 1596629, 1592053, 1561579, 1560831, 1557711, 1550962, 1513249, 1497860, 1486025, 1478067, 1466309, 1455524, 1445961, 1426434, 1411361, 1394931, 1390298, 1381010, 1369861, 1359139, 1349413, 1333670, 1332592, 1329300, 1326682, 1314313, 1294188, 1281622, 1261826, 1254861, 1242337, 1234678, 1209206, 1186479, 1185911, 1178400, 1173776, 1171823, 1171767, 1166649, 1162289, 1156357, 1134412, 1112940, 1107268, 1085492, 1083432, 1038450, 1025310, 1023694, 1023513, 1010680, 1004733, 1000776, 998996, 995781, 979729, 974909, 970879, 960059, 954440, 944603, 928913, 907747, 900176, 896486, 892774, 889863, 888983, 887611, 861067, 860747, 858878, 852681, 851452, 848450, 841132, 829845, 828449, 811215, 809449, 798676, 792382, 792333, 766127, 765849, 755850, 750883, 746259, 726114, 722765, 721732, 709641, 701106, 689366, 682046, 671107, 667370, 648524, 639616, 636521, 628660, 627666, 621422, 620885, 614897, 611735, 591399, 589869, 584554, 580722, 562892, 553848, 552912, 545671, 537595, 523537, 512931, 501342, 487603, 484130, 482682, 470347, 468370, 467857, 467183, 462738, 458149, 454601, 449703, 449600, 443333, 416022, 413356, 383619, 382541, 381500, 378438, 377571, 363731, 332759, 331393, 330240, 327425, 311222, 299242, 291610, 285675, 282250, 277419, 264990, 263850, 258206, 248992, 221228, 216755, 164227, 155796, 155480, 142529, 141646, 102381, 101042, 95159, 82486, 74131, 70770, 65114, 61658, 59654, 51886, 45867, 39165, 35143, 34706, 28669, 20399, 2674, -11864, -13085, -16956, -26621, -33077, -34249, -34638, -38911, -41035, -54813, -66431, -71682, -77698, -79719, -81733, -103361, -104953, -105632, -106642, -107736, -109863, -117818, -122430, -127360, -131440, -153760, -170183, -174151, -181143, -186281, -187104, -188098, -194877, -198053, -199095, -199341, -200213, -219824, -225572, -276453, -292458, -293994, -295103, -304909, -305120, -318869, -325393, -338894, -339540, -348517, -372017, -375023, -378032, -378170, -416154, -424253, -425556, -430931, -445346, -452892, -456297, -458945, -461692, -466377, -466677, -477006, -513959, -516083, -524425, -543976, -555315, -557940, -569214, -577973, -592066, -595600, -616117, -623392, -633484, -635022, -643492, -645549, -665709, -667418, -671539, -672292, -675002, -684334, -686857, -696949, -730827, -738950, -748882, -759558, -769527, -777436, -783662, -788646, -800874, -808195, -809932, -824319, -826553, -838343, -863892, -870933, -873994, -881955, -892134, -894878, -922992, -923733, -929079, -935990, -963416, -965415, -970154, -984309, -991459, -993168, -994650, -1011891, -1026086, -1040503, -1045224, -1049194, -1055314, -1056533, -1061430, -1064481, -1064919, -1066760, -1075704, -1086588, -1098722, -1102433, -1107070, -1108149, -1109295, -1109657, -1114613, -1120642, -1129425, -1140128, -1141285, -1143816, -1159129, -1161902, -1167277, -1167470, -1167801, -1173829, -1186410, -1190349, -1193362, -1208318, -1208873, -1214283, -1222643, -1225736, -1227877, -1232700, -1233287, -1251037, -1254774, -1272573, -1273565, -1274407, -1297343, -1301552, -1307768, -1321600, -1326026, -1326135, -1348857, -1361655, -1366226, -1370170, -1381131, -1383393, -1385686, -1385775, -1390105, -1406355, -1406918, -1415261, -1425278, -1442614, -1451028, -1455961, -1457328, -1459616, -1479076, -1494795, -1516588, -1517892, -1533701, -1539592, -1540846, -1552263, -1561773, -1574638, -1577078, -1581629, -1590490, -1603901, -1612291, -1652624, -1655463, -1663842, -1670107, -1674507, -1675462, -1679628, -1689948, -1702380, -1718453, -1732035, -1733661, -1761996, -1763115, -1767253, -1794904, -1809421, -1809626, -1811287, -1820561, -1825587, -1833499, -1833962, -1836399, -1857584, -1878630, -1882908, -1888362, -1890890, -1913826, -1923648, -1947029, -1948211, -1960202, -1981226, -1984581, -1986593, -2019712, -2021387, -2034441, -2045859, -2065210, -2071814, -2073827, -2082403, -2086770, -2090559, -2095927, -2100651, -2105786, -2110456, -2112773, -2125642, -2129045, -2130715, -2131778, -2142423 };
    
    order(big1, 512);
    order(big2, 512);
    order(big3, 512);
    
    for (int i = 0; i < 512; i++)
        assert(big1[i] == orderedBig1[i]);
    for (int i = 0; i < 512; i++)
        assert(big2[i] == orderedBig2[i]);
    for (int i = 0; i < 512; i++)
        assert(big3[i] == orderedBig3[i]);
    
    double a69[5] = { -3, 9, 8, -6, 69 };
    
    order(a69, -3);
    order(a69, 0);
    order(a69, 1);
    
    for (int i = 0; i < 5; i++)
        std::cout << a69[i] << std::endl;
    
    
    
    
    
    
    
    
    
    
    
    std::cout << "Passed all tests!" << std::endl;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*

    double a1[7] = { 10, 50, 40, 20, 50, 40, 30 };
    double a10[3] = { 10, 20, 40 };
    double a11[3] = { 10, 40, 30 };
    double a12[3] = { 20, 10, 40 };
    double a13[3] = { 50, 40, 30 };
    
    assert(countContains(a1, 7, a10, 3) == 1);
    assert(countContains(a1, 7, a11, 3) == 2);
    assert(countContains(a1, 7, a12, 3) == 0);
    assert(countContains(a1, 7, a13, 3) == 3);
    
    double a2[11] = { -20, 90, 8, 65.87, 8, 45, 23, 90, 65.87, 8, 65.87 };
    double a20[3] = { 90, 8, 65.87 };
    double a21[2] = { -20, 90 };
    
    assert(countContains(a2, 11, a20, 3) == 7);
    assert(countContains(a2, 11, a21, 2) == 2);
    
    assert(countContains(a2, -3, a20, 3) == 0);
    assert(countContains(a2, 11, a20, -99) == 1);
    

    /*
    std::cout << std::endl;
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    int fNG;
    int fL;
    separate(a1, 7, 10, fNG, fL);

    for (int i=0; i < 7; i++)
        std::cout << a1[i] << std::endl;
    
    std::cout << std::endl;
    
    order(a1, 7);
    for (int i=0; i < 7; i++)
        std::cout << a1[i] << std::endl;

    std::cout << std:: endl;

    order(a10, 3);
    for (int i=0; i < 3; i++)
        std::cout << a10[i] << std::endl;

    std::cout << std:: endl;

    order(a11, 3);
    for (int i=0; i < 3; i++)
        std::cout << a11[i] << std::endl;

    std::cout << std:: endl;

    order(a12, 3);
    for (int i=0; i < 3; i++)
        std::cout << a12[i] << std::endl;

    std::cout << std:: endl;

    order(a13, 3);
    for (int i=0; i < 3; i++)
        std::cout << a13[i] << std::endl;

    std::cout << std:: endl;
    
    double bigArr1[69] = { -21, 44, -7, -50, 13, 8, 35, 3, -57, -49, -2, 46, -20, 4, -31, 38, -4, -38, 39, 30, 2, 26, 6, -9, -55, -17, -34, -54, 23, -60, -40, 27, 7, 32, -44, 18, 22, -37, 19, -16, -36, -1, -22, 24, -56, -45, -35, -5, -11, 31, 17, 42, 47, -18, -15, 41, 9, -25, -3, 36, 40, 49, -13, -41, 48, 33, -39, -53, -52 };
    order(bigArr1, 69);
    
    double orderedBigArr1[69] = {49,48,47,46,44,42,41,40,39,38,36,35,33,32,31,30,27,26,24,23,22,19,18,17,13,9,8,7,6,4,3,2,-1,-2,-3,-4,-5,-7,-9,-11,-13,-15,-16,-17,-18,-20,-21,-22,-25,-31,-34,-35,-36,-37,-38,-39,-40,-41,-44,-45,-49,-50,-52,-53,-54,-55,-56,-57,-60 };
    
    for (int i = 0; i < 69; i++)
        assert(bigArr1[i] == orderedBigArr1[i]);
    
    double bigArr2[256] = { 94, 118, -151, 264, 143, -147, -71, 78, -63, -60, 82, 292, 299, -37, -130, 62, 303, 13, -110, 54, 100, 2, -65, 183, 290, 36, 113, 267, 11, -34, 1, 185, -77, -7, 52, 329, 161, -15, -12, 172, -45, -42, -19, 0, 218, 207, -75, 107, 3, -139, 39, 55, -10, -51, 179, 259, 242, 278, 195, 208, 313, 202, 108, 332, 65, 234, 99, 102, 109, -112, -121, 116, 33, -57, -142, -87, 200, 125, -166, 189, 237, 59, -85, -146, -141, 169, 240, 7, 217, 302, 141, 311, 233, -11, 93, 49, -92, -116, -104, 310, -150, 104, 69, 16, -99, 170, 283, 289, 157, 262, -153, 164, 328, -149, 168, -49, 117, 24, 194, 191, 187, 251, -79, 6, -40, -39, -106, 97, -47, -134, 34, 273, 17, 314, 151, 306, 44, 291, 153, 98, -128, 211, 210, 271, -74, -136, 184, 248, -101, 241, 320, 56, 317, 12, 245, -20, 171, 84, 92, 57, 247, 222, -78, 321, 277, -23, 60, 177, 244, 66, 324, -122, -148, -8, 204, -14, -155, 252, 63, 255, 293, -59, -95, 72, 31, 260, 67, 111, 178, 250, 121, -31, 196, 243, 23, 212, -113, 209, -16, 309, 64, 285, -30, 199, 198, -3, 9, 68, -115, -109, 281, -89, 51, 26, -64, 50, 45, 282, 263, -44, 37, 297, 331, 22, 265, 163, 159, -27, 165, -103, 133, -156, -88, 88, 119, 40, 322, -111, 236, 261, 19, 95, 90, 150, 91, 203, 14, 315, -28, 147, 223, 35, -56, -70, 129, 226 };
    order(bigArr2, 256);
    
    double orderedBigArr2[256] = { 332, 331, 329, 328, 324, 322, 321, 320, 317, 315, 314, 313, 311, 310, 309, 306, 303, 302, 299, 297, 293, 292, 291, 290, 289, 285, 283, 282, 281, 278, 277, 273, 271, 267, 265, 264, 263, 262, 261, 260, 259, 255, 252, 251, 250, 248, 247, 245, 244, 243, 242, 241, 240, 237, 236, 234, 233, 226, 223, 222, 218, 217, 212, 211, 210, 209, 208, 207, 204, 203, 202, 200, 199, 198, 196, 195, 194, 191, 189, 187, 185, 184, 183, 179, 178, 177, 172, 171, 170, 169, 168, 165, 164, 163, 161, 159, 157, 153, 151, 150, 147, 143, 141, 133, 129, 125, 121, 119, 118, 117, 116, 113, 111, 109, 108, 107, 104, 102, 100, 99, 98, 97, 95, 94, 93, 92, 91, 90, 88, 84, 82, 78, 72, 69, 68, 67, 66, 65, 64, 63, 62, 60, 59, 57, 56, 55, 54, 52, 51, 50, 49, 45, 44, 40, 39, 37, 36, 35, 34, 33, 31, 26, 24, 23, 22, 19, 17, 16, 14, 13, 12, 11, 9, 7, 6, 3, 2, 1, 0, -3, -7, -8, -10, -11, -12, -14, -15, -16, -19, -20, -23, -27, -28, -30, -31, -34, -37, -39, -40, -42, -44, -45, -47, -49, -51, -56, -57, -59, -60, -63, -64, -65, -70, -71, -74, -75, -77, -78, -79, -85, -87, -88, -89, -92, -95, -99, -101, -103, -104, -106, -109, -110, -111, -112, -113, -115, -116, -121, -122, -128, -130, -134, -136, -139, -141, -142, -146, -147, -148, -149, -150, -151, -153, -155, -156, -166 };
    
    for (int i = 0; i < 256; i++)
        assert(bigArr2[i] == orderedBigArr2[i]);
    
    
    std::cout << "Passed all tests!" << std::endl;*/
}
