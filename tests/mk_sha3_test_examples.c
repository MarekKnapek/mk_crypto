#include "mk_sha3_test_examples.h"

#include "../utils/mk_assert.h"
#include "../utils/mk_inline.h"

#include "../src/mk_sha3_224.h"
#include "../src/mk_sha3_256.h"
#include "../src/mk_sha3_384.h"
#include "../src/mk_sha3_512.h"
#include "../src/mk_sha3_shake128.h"
#include "../src/mk_sha3_shake256.h"

#include <stddef.h> /* size_t offsetof */
#include <string.h> /* memcmp */


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable:4820) /* warning C4820: 'xxx': 'xxx' bytes padding added after data member 'xxx' */
#endif


#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverlength-strings" /* warning: string length 'xxx' is greater than the length '509' ISO C90 compilers are required to support */
#endif


/* https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values */


static char const s_msg_0[] = "";
static char const s_msg_1[] = "11001";
static char const s_msg_2[] = "110010100001101011011110100110";
static char const s_msg_3[] = "1100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101";
static char const s_msg_4[] = "110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000";
static char const s_msg_5[] = "1100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001011100010111000101110001";

static char const s_sha3_224_0[] = "6B4E03423667DBB73B6E15454F0EB1ABD4597F9A1B078E3F5B5A6BC7";
static char const s_sha3_224_1[] = "FFBAD5DA96BAD71789330206DC6768ECAEB1B32DCA6B3301489674AB";
static char const s_sha3_224_2[] = "D666A514CC9DBA25AC1BA69ED3930460DEAAC9851B5F0BAAB007DF3B";
static char const s_sha3_224_3[] = "9376816ABA503F72F96CE7EB65AC095DEEE3BE4BF9BBC2A1CB7E11E0";
static char const s_sha3_224_4[] = "22D2F7BB0B173FD8C19686F9173166E3EE62738047D7EADD69EFB228";
static char const s_sha3_224_5[] = "4E907BB1057861F200A599E9D4F85B02D88453BF5B8ACE9AC589134C";

static char const s_sha3_256_0[] = "A7FFC6F8BF1ED76651C14756A061D662F580FF4DE43B49FA82D80A4B80F8434A";
static char const s_sha3_256_1[] = "7B0047CF5A456882363CBF0FB05322CF65F4B7059A46365E830132E3B5D957AF";
static char const s_sha3_256_2[] = "C8242FEF409E5AE9D1F1C857AE4DC624B92B19809F62AA8C07411C54A078B1D0";
static char const s_sha3_256_3[] = "79F38ADEC5C20307A98EF76E8324AFBFD46CFD81B22E3973C65FA1BD9DE31787";
static char const s_sha3_256_4[] = "81EE769BED0950862B1DDDED2E84AAA6AB7BFDD3CEAA471BE31163D40336363C";
static char const s_sha3_256_5[] = "52860AA301214C610D922A6B6CAB981CCD06012E54EF689D744021E738B9ED20";

static char const s_sha3_384_0[] = "0C63A75B845E4F7D01107D852E4C2485C51A50AAAA94FC61995E71BBEE983A2AC3713831264ADB47FB6BD1E058D5F004";
static char const s_sha3_384_1[] = "737C9B491885E9BF7428E792741A7BF8DCA9653471C3E148473F2C236B6A0A6455EB1DCE9F779B4B6B237FEF171B1C64";
static char const s_sha3_384_2[] = "955B4DD1BE03261BD76F807A7EFD432435C417362811B8A50C564E7EE9585E1AC7626DDE2FDC030F876196EA267F08C3";
static char const s_sha3_384_3[] = "1881DE2CA7E41EF95DC4732B8F5F002B189CC1E42B74168ED1732649CE1DBCDD76197A31FD55EE989F2D7050DD473E8F";
static char const s_sha3_384_4[] = "A31FDBD8D576551C21FB1191B54BDA65B6C5FE97F0F4A69103424B43F7FDB835979FDBEAE8B3FE16CB82E587381EB624";
static char const s_sha3_384_5[] = "3485D3B280BD384CF4A777844E94678173055D1CBC40C7C2C3833D9EF12345172D6FCD31923BB8795AC81847D3D8855C";

static char const s_sha3_512_0[] = "A69F73CCA23A9AC5C8B567DC185A756E97C982164FE25859E0D1DCC1475C80A615B2123AF1F5F94C11E3E9402C3AC558F500199D95B6D3E301758586281DCD26";
static char const s_sha3_512_1[] = "A13E01494114C09800622A70288C432121CE70039D753CADD2E006E4D961CB27544C1481E5814BDCEB53BE6733D5E099795E5E81918ADDB058E22A9F24883F37";
static char const s_sha3_512_2[] = "9834C05A11E1C5D3DA9C740E1C106D9E590A0E530B6F6AAA7830525D075CA5DB1BD8A6AA981A28613AC334934A01823CD45F45E49B6D7E6917F2F16778067BAB";
static char const s_sha3_512_3[] = "E76DFAD22084A8B1467FCF2FFA58361BEC7628EDF5F3FDC0E4805DC48CAEECA81B7C13C30ADF52A3659584739A2DF46BE589C51CA1A4A8416DF6545A1CE8BA00";
static char const s_sha3_512_4[] = "FC4A167CCB31A937D698FDE82B04348C9539B28F0C9D3B4505709C03812350E4990E9622974F6E575C47861C0D2E638CCFC2023C365BB60A93F528550698786B";
static char const s_sha3_512_5[] = "CF9A30AC1F1F6AC0916F9FEF1919C595DEBE2EE80C85421210FDF05F1C6AF73AA9CAC881D0F91DB6D034A2BBADC1CF7FBCB2ECFA9D191D3A5016FB3FAD8709C9";

static char const s_sha3_shake128_4096_0[] = "7F9C2BA4E88F827D616045507605853ED73B8093F6EFBC88EB1A6EACFA66EF263CB1EEA988004B93103CFB0AEEFD2A686E01FA4A58E8A3639CA8A1E3F9AE57E235B8CC873C23DC62B8D260169AFA2F75AB916A58D974918835D25E6A435085B2BADFD6DFAAC359A5EFBB7BCC4B59D538DF9A04302E10C8BC1CBF1A0B3A5120EA17CDA7CFAD765F5623474D368CCCA8AF0007CD9F5E4C849F167A580B14AABDEFAEE7EEF47CB0FCA9767BE1FDA69419DFB927E9DF07348B196691ABAEB580B32DEF58538B8D23F87732EA63B02B4FA0F4873360E2841928CD60DD4CEE8CC0D4C922A96188D032675C8AC850933C7AFF1533B94C834ADBB69C6115BAD4692D8619F90B0CDF8A7B9C264029AC185B70B83F2801F2F4B3F70C593EA3AEEB613A7F1B1DE33FD75081F592305F2E4526EDC09631B10958F464D889F31BA010250FDA7F1368EC2967FC84EF2AE9AFF268E0B1700AFFC6820B523A3D917135F2DFF2EE06BFE72B3124721D4A26C04E53A75E30E73A7A9C4A95D91C55D495E9F51DD0B5E9D83C6D5E8CE803AA62B8D654DB53D09B8DCFF273CDFEB573FAD8BCD45578BEC2E770D01EFDE86E721A3F7C6CCE275DABE6E2143F1AF18DA7EFDDC4C7B70B5E345DB93CC936BEA323491CCB38A388F546A9FF00DD4E1300B9B2153D2041D205B443E41B45A653F2A5C4492C1ADD544512DDA2529833462B71A41A45BE97290B6F";
static char const s_sha3_shake128_4096_1[] = "2E0ABFBA83E6720BFBC225FF6B7AB9FFCE58BA027EE3D898764FEF287DDECCCA3E6E5998411E7DDB32F67538F500B18C8C97C452C370EA2CF0AFCA3E05DE7E4DE27FA441A9CB34FD17C978B42D5B7E7F9AB18FFEFFC3C5AC2F3A455EEBFDC76CEAEB0A2CCA22EEF6E637F4CABE5C51DED2E3FAD8B95270A321845664F107D16496BB7ABFBE7504B6EDE2E89E4B996FB58EFDC4181F9163381CBE7BC006A7A205989C526CD1BD68983693B4BDC53728B241C1CFF42BB611502C35205CABB288755655D620C67994F06451187F6FD17E046682BA1286063FF88FE2508D1FCAF9035A1231AD4150A9C9B24C9B2D66B2AD1BDE0BD0BBCB8BE05B835229EF7919737323424401E1D837B66EB4E630FF1DE70CB317C2BACB08001D3477B7A70A576D20869033589D85A01DDB2B6646C043B59FC011311DA666FA5AD1D6387FA9BC4015A38A51D1DA1EA61D648DC8E39A88B9D622BDE207FDABC6F2827A880C330BBF6DF733774B653E57305D78DCE112F10A2C71F4CDAD92ED113E1CEA63B91925ED28191E6DBBB5AA5A2AFDA51FC05A3AF5258B87665243550F28948AE2B8BEB6BC9C770B35F067EAA641EFE65B1A44909D1B149F97EEA601391C609EC81D1930F57C18A4E0FAB491D1CADFD50483449EDC0F07FFB24D2C6F9A9A3BFF39AE3D57F560654D7D75C908ABE62564753EAC39D7503DA6D37C2E32E1AF3B8AEC8AE3069CD9";
static char const s_sha3_shake128_4096_2[] = "6D5D39C55F3CCA567FEAF422DC64BA17401D07756D78B0FA3D546D66AFC27671E0010685FC69A7EC3C5367B8FA5FDA39D57CE53F153FA4031D277206770AEC6B2DDF16AEFAB669110D6E4A296A14FB1486B0846B690543E4057F7F42AA8C0E6A5A56B60B688D55A196DF6F3976E30688CBB6AFD48525D76490357F3FD897BAFC8736D907B9BAC816591FC24E79360BE3A7FFA62982C45ABB0E584C07EC93A19530509D9F816215D7277BB999437C821450F0759281CD8E16A3483E3CC752091B7AAE92909D2F501EF7DCE989759891B3377CEAB493FFE496010A0C7E51959994F56F565E633AF6093AC6E1E0F0048871EC4778F48EF8BD5BCB80EA7DF9FF4711C81E24C0221C2AD9744FBA7935EAECA114224FD108EFC5AC74C66252089275B4277673708C4AF92F8813B193599FD64BD7484F2E5EC369E3646499768E581DD053AA4814D8BF1ACFF5FD774519A749BE66754741EBC5362212A9FEA8A814E9E010BC2720B3B7D94FAB74BC7F923E1072B8A5DDDDA83BA0157D8CBA55C192DF6965CB7DBA46A3340DF8C3FA89C7C4DB539D38DC406F1D2CF54E5905580B4404BFD7B3719561C5A59D5DFDB1BF93DF13825225EDCCE0FA7D87EFCD239FEB49FC9E2DE9D828FEEB1F2CF579B95DD050AB2CA47105A8D30F3FD2A1154C15F87FB37B2C7156BD7F3CF2B745C912A40BC1B559B656E3E903CC5733E86BA15DFEF70678";
static char const s_sha3_shake128_4096_3[] = "131AB8D2B594946B9C81333F9BB6E0CE75C3B93104FA3469D3917457385DA037CF232EF7164A6D1EB448C8908186AD852D3F85A5CF28DA1AB6FE3438171978467F1C05D58C7EF38C284C41F6C2221A76F12AB1C04082660250802294FB87180213FDEF5B0ECB7DF50CA1F8555BE14D32E10F6EDCDE892C09424B29F597AFC270C904556BFCB47A7D40778D390923642B3CBD0579E60908D5A000C1D08B98EF933F806445BF87F8B009BA9E94F7266122ED7AC24E5E266C42A82FA1BBEFB7B8DB0066E16A85E0493F07DF4809AEC084A593748AC3DDE5A6D7AAE1E8B6E5352B2D71EFBB47D4CAEED5E6D633805D2D323E6FD81B4684B93A2677D45E7421C2C6AEA259B855A698FD7D13477A1FE53E5A4A6197DBEC5CE95F505B520BCD9570C4A8265A7E01F89C0C002C59BFEC6CD4A5C109258953EE5EE70CD577EE217AF21FA70178F0946C9BF6CA8751793479F6B537737E40B6ED28511D8A2D7E73EB75F8DAAC912FF906E0AB955B083BAC45A8E5E9B744C8506F37E9B4E749A184B30F43EB188D855F1B70D71FF3E50C537AC1B0F8974F0FE1A6AD295BA42F6AEC74D123A7ABEDDE6E2C0711CAB36BE5ACB1A5A11A4B1DB08BA6982EFCCD716929A7741CFC63AA4435E0B69A9063E880795C3DC5EF3272E11C497A91ACF699FEFEE206227A44C9FB359FD56AC0A9A75A743CFF6862F17D7259AB075216C0699511643B6439";
static char const s_sha3_shake128_4096_4[] = "4AC38EBD1678B4A452792C5673F9777D36B55451AAAE2424924942D318A2F6F51BBC837DCC7022C5403B69D29AC99A745F06D06F2A41B0CC243CD270FA44D43065AF00D2AD358BD5A5D06D331BC230CD8DDA4655628F9102711ADAFB7636C160B2D25EC6235A2FE0F37394D87FC5FFD7DBF1993E558AEBEA6C61E907188C61F5FCDE278E264F958FFD7B3382DC10139B625E1241AB5BBC2A1FBCAC31A335CFC7B20E427712246CBB55232259A7EF1602BD56F6567D66942D4A7149F4222210B074EA54154B38E8FDFA0DCF4FA3ECD2154E8318A6578B535DBCFC217A3CAB52532965846F89781457025563E2DC15CC3AF902BA2AD280FFBBBFA4C52B60FA41BAC21F4AB23536268119FC98CD982DA5CD5DA21E1B5692D47105DE9F1E0132C6FE315D67FA464997C2AB5533C79F98E6E64FF80802A7FE96CA04A81F885527370A2206B10B3936DD81B8246353F4CD90511089268D744F210AC689D49D2875054A727B604D13D269B37190D427C7D15CCCDCD7870E0B8ADBEB977111A9BCF7781A161356A5941C799907EF9D3B1A441F09515F2831C4FAFDE3DC7C1E9B5AA57D3E83CD6734DA3D8B9EF3FC448805EA29C99CBA6B352BCABE2FD970AE9580D2BF25152B960E6B806D87D7D0608B247F61089E298692C27F19C52D03EBE395A36806AD540BEC2D046C18E355FAF8313D2EF8995EE6AAE42568F314933E3A21E5BE40";
static char const s_sha3_shake128_4096_5[] = "89846DC776AC0F014572EA79F560773451002938248E6882569AC32AEAB191FCACDE68EB07557539C4845FB444108E6E0545E731FCCA2D4F67A3BFD41CFF3EAF35EEFB53441177965BB516950CF5DCB2AAFCBBC6300E8EEFD9BCD0E5F32D1A4E872E0F1DBD8F8E00CBB878698C5883E3CA184B9490389E46002C08A0B16B05A36B2CB5A1CAE08E11AD972FD24AF70101CE4746C84F1671877F0DF6C415D1670FF40B8DDEDD89CC3E656DB9058049D609B6784CC9D05E60CC6AC9C8194993BA29158FD4DB8CF225E9574F18A77F66EC1052BF17993BDA206A17737D785BD4C18CEE4C76AA5735A5223F3C55E79DAEC13D4BF60F1562E0AD0FA3B558ECCFA8AB3EEF61474D576E8CAF4C11E4DE5CCB36D7DF7D892C1FCA2017BE8BBDA5A47195448CC67A078E628A2EF763FFE1DC9D9D6FF78E68961C33FFD9000C11DEE7F7408D8DA5C605B0B4D56BB55E9364C77BFAD9C8191ED6E1FE7B7A937C6D07095FE5EA91A700B4BDFC17B428D036922AA8AB5E2CD585846FB81FC693B8D59BF85C74BC700CD2BC3E6AAB437D93D8A30F1CF692EFEF43602028E0CE5742EB3F4F4D5B029158DD6896ACB5E3A7F684D9AA8914E70974B223A6FEC38D76C7473E86E4B9B32C621E2015C55E947DD016C675C82368CE26FB456A5B65881AF513BFDC88687C6381676ABBD2D9104ED23A9E89310246B026CEDD57595B1AB6FE88A784BE0C06";

static char const s_sha3_shake256_4096_0[] = "46B9DD2B0BA88D13233B3FEB743EEB243FCD52EA62B81B82B50C27646ED5762FD75DC4DDD8C0F200CB05019D67B592F6FC821C49479AB48640292EACB3B7C4BE141E96616FB13957692CC7EDD0B45AE3DC07223C8E92937BEF84BC0EAB862853349EC75546F58FB7C2775C38462C5010D846C185C15111E595522A6BCD16CF86F3D122109E3B1FDD943B6AEC468A2D621A7C06C6A957C62B54DAFC3BE87567D677231395F6147293B68CEAB7A9E0C58D864E8EFDE4E1B9A46CBE854713672F5CAAAE314ED9083DAB4B099F8E300F01B8650F1F4B1D8FCF3F3CB53FB8E9EB2EA203BDC970F50AE55428A91F7F53AC266B28419C3778A15FD248D339EDE785FB7F5A1AAA96D313EACC890936C173CDCD0FAB882C45755FEB3AED96D477FF96390BF9A66D1368B208E21F7C10D04A3DBD4E360633E5DB4B602601C14CEA737DB3DCF722632CC77851CBDDE2AAF0A33A07B373445DF490CC8FC1E4160FF118378F11F0477DE055A81A9EDA57A4A2CFB0C83929D310912F729EC6CFA36C6AC6A75837143045D791CC85EFF5B21932F23861BCF23A52B5DA67EAF7BAAE0F5FB1369DB78F3AC45F8C4AC5671D85735CDDDB09D2B1E34A1FC066FF4A162CB263D6541274AE2FCC865F618ABE27C124CD8B074CCD516301B91875824D09958F341EF274BDAB0BAE316339894304E35877B0C28A9B1FD166C796B9CC258A064A8F57E27F2A";
static char const s_sha3_shake256_4096_1[] = "48A5C11ABAEEFF092F3646EF0D6B3D3FF76C2F55F9C732AC6470C03764008212E21B1467778B181989F88858211B45DF8799CF961F800DFAC99E644039E2979A4016F5456FF421C5B385DA2B855DA7E31C8C2E8E4BA41EB4095CB999D9759CB40358DA8562A2E61349E05A2E13F1B74EC9E69F5B426DC74138FFCDC571C32B39B9F55563E1A99DC422C306026D6A0F9DE85162B386794CA0688B764B3D32200CC459749732A0F3A341C0EFC96A22C63BAD7D96CC9BA4768C6FCFA1F200107CF9FAE5C0D754958C5A756B376A3BE69F88074F200E9E95A8CA5BCF969998DB1DC37D0D3D916F6CAAB3F03782C9C44A2E14E80786BECE4587B9EF82CBF454E0E34BD175AE57D36AF4E726B221332CED36C8CE2E06203C656AE8DA037D08E7160B480C1A8516BF06DD97BF4AA4C0249310DC0B065DC639576355384D165C6A509B12F7BBD1E15B22BCE02FA048DDFAACF7415F49B6324C1D067B5264E1125F7F75427F312BD9346EB4E400B1F7CB31288C9E3F735ECA9CED0DB888E2E2F402243BD64618A23E10F9C229397440542D0AB1B2E10DACC5C95E597F2C7EA38438105F97803DBB03FCC0FD416B0905A41D184DEB238905775891F93501FB4176A3BD6C464461D36EE8B008AABD9E26A34055E80C8C813EEBA07F728AB32B15605AD161A0669F6FCE5C5509FBB6AFD24AEACC5FA4A51523E6B173246ED4BFA521D74FC6BB";
static char const s_sha3_shake256_4096_2[] = "465D081DFF875E396200E4481A3E9DCD88D079AA6D66226CB6BA454107CB81A7841AB02960DE279CCBE34B42C36585AD86964DB0DB52B6E7B4369ECE8F7248589BA78AB1828FFC335CB12397119BFD2B87EB7898AEB956B6F23DDF0BD4004386A8E526554EF4E483FACEE30DD32E204FFF8C36BBD602A576D139089C75A8050266FCBF721E4443DE4645832922EB8AAE39D1F572845364817B0033543899940023F2E965A60A80EB221EB19DC57B121291564C6F693583B3AC7C6F272F4F67A19A7678D4234B0BF4A2EBC08AA235B9788DB787161F6617022865C0EF9AA533802D136CDBC7AEBA532ACF1BE183B0295AB0E33A2EF69BE356DAAF309687153E2F99A1243609D603126A8C823E8843E459BFC72B30691CDCC3DDB27CF028AFD51E4437EE3B71C0C1EC87A93436F0C247B7E8C50CE96825C97029997A74C318AFACAA18A0180BC7F2F0F1C5E7EF1A2D183AC7EE7E4915C3B68C30978AB6C428193441DF4705B722CE25A08A1FADCA0EEF1FAFE83ADF13021D520DE5C827FF9A97B75546193A9B923F0590385DC4BFF7C49D4915B5A365DB4C84DDCB185DE8F9EEB334965A42F1381C8BADC22BA1F8EE4C0E4DAAF7A88E7F42DDB8148F3BF8D3B8D74F098155A37CB4CB27876B85DA602E5C789C10E03BE73407BAB8C49213F8C74E1266CE9B11286E674CA9C10C9C9955049A66E9051D9A2B1FC9AFE26798E9CEC6";
static char const s_sha3_shake256_4096_3[] = "CD8A920ED141AA0407A22D59288652E9D9F1A7EE0C1E7C1CA699424DA84A904D2D700CAAE7396ECE96604440577DA4F3AA22AEB8857F961C4CD8E06F0AE6610B1048A7F64E1074CD629E85AD7566048EFC4FB500B486A3309A8F26724C0ED628001A1099422468DE726F1061D99EB9E93604D5AA7467D4B1BD6484582A384317D7F47D750B8F5499512BB85A226C4243556E696F6BD072C5AA2D9B69730244B56853D16970AD817E213E470618178001C9FB56C54FEFA5FEE67D2DA524BB3B0B61EF0E9114A92CDBB6CCCB98615CFE76E3510DD88D1CC28FF99287512F24BFAFA1A76877B6F37198E3A641C68A7C42D45FA7ACC10DAE5F3CEFB7B735F12D4E589F7A456E78C0F5E4C4471FFFA5E4FA0514AE974D8C2648513B5DB494CEA847156D277AD0E141C24C7839064CD08851BC2E7CA109FD4E251C35BB0A04FB05B364FF8C4D8B59BC303E25328C09A882E952518E1A8AE0FF265D61C465896973D7490499DC639FB8502B39456791B1B6EC5BCC5D9AC36A6DF622A070D43FED781F5F149F7B62675E7D1A4D6DEC48C1C7164586EAE06A51208C0B791244D307726505C3AD4B26B6822377257AA152037560A739714A3CA79BD605547C9B78DD1F596F2D4F1791BC689A0E9B799A37339C04275733740143EF5D2B58B96A363D4E08076A1A9D7846436E4DCA5728B6F760EEF0CA92BF0BE5615E96959D767197A0BEEB";
static char const s_sha3_shake256_4096_4[] = "98D093B067475760124FFB9204A5B327C6BB05C54FF234F0B43FAC7240415166A8C705EA0D739F0808B06576D996662C1F376694D98F515719B66407720DCF781C51CD56EF8B610C668DDC1AC1C2C429EA4D6F274AA7A773BF8B0CAB306F1EEE2A171B91334EA0FACD2AAC1F51D4D5EB0E63A4E6754ECAFEEC246B7AAF58D0E0A974C7FF4058BDBDEDB33ED04B0FA45D70C7C84F3DA13E4F7D1BEDDB534D37E5ABDFB29F2B44C4FB0D6CCAB831D90BA46A00530662F907DEDD479E9B5428E5E2DB8040B0E2B1F174CE347F32A06A5AC22B19AAFE927B8878D0C8103A4D2F19E32336C64CFADC1B9ACB3978A8298571DCD89C36A65692816D0C61CE0ED17942367017BD40F59DFBAE34635827920AFE7A27BF567009A138403F06B6E4DE94DA077DB49773C235466119426F79888D3A81B407DFEBA87E01CD48F90E01B6F90243C40125DE47E8C8F3E6EA3388CBFEEB36541EF23D2C8348458EA28CAA5066F4983776F0CB2FDC66049CF88AC8EAE51212AACE867BEA4C3CAEE44F147A9BF99D04874E8722D03D3F5FF6EF3BEBE7642FE4916C5F10FF3FD61387D5D91BCD32F9E8E4593DCAAD23ECCC05D2FC9BE2C1CD630EA123DCA9CB6938D60CDDEDC11E1E9BC9D268A5456BA9CCFF18597C5FF9735708413B9D84B9F4721937CC6595712797532B48D6F1A2D1723B07D5460BC13916D96E88180713AC33D2C232E35E764E04";
static char const s_sha3_shake256_4096_5[] = "8A8325079B0FC3265D52F59855CAFE655DF438AA639F6FEC991F2494330CE32FA37F7DB90F6966D8E4A46E50C5EDE57B9B8F082A96627F730475029A619229D84F432ED69FD059234D4D7DD358E8393F6A36A45CCF041F90FC0A4E5802D73063D36531336A0090ECFE1A4D4D29AA824BA42B4937B4BB98F4F33A0E3BD8B511E69528D59537110D7521FB78ACA018DF76160F54A3421B84149264ED032F6DCE467A731A8E34048E3A46E98039DF3C328DEBFBE5D1BC8BE7FF4EF8917B01F0B7893672492D6EE5C71DF2D0531F8B684764BA0A2B57EC6A4F60BA4F36FE2DB0E65AD7AA5F14F3EF9F34A0AB5BC33D488733BA36BF4B2B4FCE028EFF8C6CE03B192CF075CC9F00D29C0E06C35C4489D27F07FA49A91CA92471E34DAB7787AE24A6E0F309EF0BA53F7C8B2992520A07BEDD509A0B6DBEA570A5960ED624826DD8ECD1915C87327E74491C405A7411C12C0D4497512689BD7F5ADBEDB02C6D2E68474E8BF31B884040818F4BCA03A45217EAC7083AD3A33CB8477A04C9E3266A133477DE45E71830A40EB0D075AFCCFCD9DC548D0D529460EA7AC2ADAC722E7678EF597DD3B495BD7D1A8FF39448BBAB1DC6A88481801CF5A8010E873C31E479A5E3DB3D4E67D1D948E67CC66FD75A4A19C120662EF55977BDDBAC0721C80D69902693C83D5EF7BC27EFA393AF4C439FC39958E0E75537358802EF0853B7470B0F19AC";


#define mk_check(x) do{ if(!(x)){ return __LINE__; } }while(0)
#define mk_try(x) do{ int err; err = (x); if(err != 0){ return err; } }while(0)


static mk_inline void mk_string_bin_to_bytes(char const* in, int len, void* out)
{
	unsigned char* output;
	int i;
	int byte;
	int bit;

	mk_assert(in);
	mk_assert(len >= 0);
	mk_assert(out);

	output = (unsigned char*)out;
	for(i = 0; i != len; ++i)
	{
		byte = i / CHAR_BIT;
		bit = i % CHAR_BIT;
		if(in[i] == '1')
		{
			output[byte] = (output[byte] & ~(1u << bit)) | (unsigned char)(1u << bit);
		}
		else
		{
			mk_assert(in[i] == '0');
			output[byte] = (output[byte] & ~(1u << bit));
		}
	}
}

static mk_inline int mk_hex_symbol_to_int(char const hs)
{
	static char const s_hex_alphabet_lc[] = "0123456789abcdef";
	static char const s_hex_alphabet_uc[] = "0123456789ABCDEF";

	int i;

	for(i = 0; i != sizeof(s_hex_alphabet_lc) - 1; ++i)
	{
		if(hs == s_hex_alphabet_lc[i])
		{
			break;
		}
		if(hs == s_hex_alphabet_uc[i])
		{
			break;
		}
	}
	return i;
}

static mk_inline void mk_string_hex_to_bytes(void const* in, int len, void* out)
{
	char const* input;
	unsigned char* output;
	int i;
	int hi;
	int lo;

	mk_assert(in);
	mk_assert(out);
	mk_assert(len % 2 == 0);

	input = (char const*)in;
	output = (unsigned char*)out;
	for(i = 0; i != len / 2; ++i)
	{
		hi = mk_hex_symbol_to_int(input[2 * i + 0]);
		lo = mk_hex_symbol_to_int(input[2 * i + 1]);
		output[i] = (unsigned char)((hi << 4) | (lo << 0));
	}
}

static mk_inline void mk_sha3_shake128_finish_4096(struct mk_sha3_shake128_state_s* self, void* digest)
{
	mk_assert(self);
	mk_assert(digest);

	mk_sha3_shake128_finish(self, digest, 4096);
}

static mk_inline void mk_sha3_shake256_finish_4096(struct mk_sha3_shake256_state_s* self, void* digest)
{
	mk_assert(self);
	mk_assert(digest);

	mk_sha3_shake256_finish(self, digest, 4096);
}


int mk_sha3_test_examples(void)
{
	struct msg_and_digests_s
	{
		char const* m_msg_str_bin;
		int m_msg_len;
		char const* m_sha3_str_hex_224;
		char const* m_sha3_str_hex_256;
		char const* m_sha3_str_hex_384;
		char const* m_sha3_str_hex_512;
		char const* m_sha3_str_hex_shake128_4096;
		char const* m_sha3_str_hex_shake256_4096;
	};

	static struct msg_and_digests_s s_msgs_and_digests[] =
	{
		{s_msg_0, sizeof(s_msg_0) - 1, s_sha3_224_0, s_sha3_256_0, s_sha3_384_0, s_sha3_512_0, s_sha3_shake128_4096_0, s_sha3_shake256_4096_0},
		{s_msg_1, sizeof(s_msg_1) - 1, s_sha3_224_1, s_sha3_256_1, s_sha3_384_1, s_sha3_512_1, s_sha3_shake128_4096_1, s_sha3_shake256_4096_1},
		{s_msg_2, sizeof(s_msg_2) - 1, s_sha3_224_2, s_sha3_256_2, s_sha3_384_2, s_sha3_512_2, s_sha3_shake128_4096_2, s_sha3_shake256_4096_2},
		{s_msg_3, sizeof(s_msg_3) - 1, s_sha3_224_3, s_sha3_256_3, s_sha3_384_3, s_sha3_512_3, s_sha3_shake128_4096_3, s_sha3_shake256_4096_3},
		{s_msg_4, sizeof(s_msg_4) - 1, s_sha3_224_4, s_sha3_256_4, s_sha3_384_4, s_sha3_512_4, s_sha3_shake128_4096_4, s_sha3_shake256_4096_4},
		{s_msg_5, sizeof(s_msg_5) - 1, s_sha3_224_5, s_sha3_256_5, s_sha3_384_5, s_sha3_512_5, s_sha3_shake128_4096_5, s_sha3_shake256_4096_5},
	};

	typedef void(*alg_init_t)(void*);
	typedef void(*alg_append_t)(void*, void const*, size_t);
	typedef void(*alg_finish_t)(void*, void*);

	struct alg_descr_s
	{
		int m_digest_offset;
		int m_digest_len;
		alg_init_t m_init;
		alg_append_t m_append;
		alg_finish_t m_finish;
	};

	static struct alg_descr_s const s_alg_descrs[] =
	{
		{offsetof(struct msg_and_digests_s, m_sha3_str_hex_224),            28, (alg_init_t)&mk_sha3_224_init,      (alg_append_t)&mk_sha3_224_append_bits,      (alg_finish_t)mk_sha3_224_finish},
		{offsetof(struct msg_and_digests_s, m_sha3_str_hex_256),            32, (alg_init_t)&mk_sha3_256_init,      (alg_append_t)&mk_sha3_256_append_bits,      (alg_finish_t)mk_sha3_256_finish},
		{offsetof(struct msg_and_digests_s, m_sha3_str_hex_384),            48, (alg_init_t)&mk_sha3_384_init,      (alg_append_t)&mk_sha3_384_append_bits,      (alg_finish_t)mk_sha3_384_finish},
		{offsetof(struct msg_and_digests_s, m_sha3_str_hex_512),            64, (alg_init_t)&mk_sha3_512_init,      (alg_append_t)&mk_sha3_512_append_bits,      (alg_finish_t)mk_sha3_512_finish},
		{offsetof(struct msg_and_digests_s, m_sha3_str_hex_shake128_4096), 512, (alg_init_t)&mk_sha3_shake128_init, (alg_append_t)&mk_sha3_shake128_append_bits, (alg_finish_t)mk_sha3_shake128_finish_4096},
		{offsetof(struct msg_and_digests_s, m_sha3_str_hex_shake256_4096), 512, (alg_init_t)&mk_sha3_shake256_init, (alg_append_t)&mk_sha3_shake256_append_bits, (alg_finish_t)mk_sha3_shake256_finish_4096},
	};

	union alg_states_u
	{
		struct mk_sha3_224_state_s m_224;
		struct mk_sha3_256_state_s m_256;
		struct mk_sha3_384_state_s m_384;
		struct mk_sha3_512_state_s m_512;
		struct mk_sha3_shake128_state_s m_shake128;
		struct mk_sha3_shake256_state_s m_shake256;
	};


	int msgs;
	int i;
	unsigned char msg_bytes[204];
	int algs;
	int j;
	char const* digest_baseline_str_hex;
	unsigned char digest_baseline[512];
	union alg_states_u alg_state;
	unsigned char digest_computed[512];
	int compared;

	msgs = sizeof(s_msgs_and_digests) / sizeof(s_msgs_and_digests[0]);
	for(i = 0; i != msgs; ++i)
	{
		mk_string_bin_to_bytes(s_msgs_and_digests[i].m_msg_str_bin, s_msgs_and_digests[i].m_msg_len, msg_bytes);
		algs = sizeof(s_alg_descrs) / sizeof(s_alg_descrs[0]);
		for(j = 0; j != algs; ++j)
		{
			digest_baseline_str_hex = *(char const**)((char*)&s_msgs_and_digests[i] + s_alg_descrs[j].m_digest_offset);
			mk_string_hex_to_bytes(digest_baseline_str_hex, s_alg_descrs[j].m_digest_len * 2, digest_baseline);
			s_alg_descrs[j].m_init(&alg_state);
			s_alg_descrs[j].m_append(&alg_state, &msg_bytes, s_msgs_and_digests[i].m_msg_len);
			s_alg_descrs[j].m_finish(&alg_state, &digest_computed);
			compared = memcmp(&digest_computed, &digest_baseline, s_alg_descrs[j].m_digest_len);
			mk_assert(compared == 0);
			mk_check(compared == 0);
		}
	}

	return 0;
}


#undef mk_check
#undef mk_try


#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
