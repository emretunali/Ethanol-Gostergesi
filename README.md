# Ethanol-Gostergesi
Arduino Uno,Nano, Pro Mini Platformları üzerine kurulmuş ethanol göstergesi. LCD olarak Nextion kullanılmıştır.

Devreyi kurup elektrik verdiğinizde eğer bağlantıları doğru yaptıysanız gösterge 0 dan 100e kadar sayıp sonrasında sensörden gelen bilgiyi gösterecektir. Eğer sürekli ekranda 254 değerini alıyorsanız Arduino ile nextion lcd arasındaki rx tx uçlarını yanlış bağlamışsınız demekdir. Uçları ters çevirmeniz yeterli olacaktır. İllaki arduino uno kullanmanıza gerek yok. Aynı kodları nano, pro mini içinde kullanabilirsiniz. Projenin ticari hiç bir amacı yoktur. İstediğiniz gibi geliştirebilir, dağıtabilir ve yapıp satabilirsiniz. İlerliyen güncellemelerde oled ve 2x16 lcd bağlantılarınıda ekleyeceğim.

Takıldığınız bir yer olursa e.tunali@sparkems.com.tr mail adresimden bana ulaşabilirsiniz.

* V1.0.0 - Continental Flex Fuel Sensorden alınan veriler işlendi
*        - Nextion 2.8" Lcd'ye görüntü aktarıldı ve test edildi çalışıyor.
* V1.0.1 - 2x16 LCD eklemesi yapıldı. ( Test Edilmedi ! )

# bilgipaylaştıkçaçoğalır
# kendinyap
# kendinöğren

# Malzemeleri satın alacağınız siteler

# Arduino UNO              : https://www.direnc.net/arduino-uno-r3-smd
# 4.7k Direnç              : https://www.direnc.net/47k-14w-direnc-1
# Nextion 2.8inç LCD       : https://www.direnc.net/2-8-inch-nextion-hmi-dokunmatik-tft-lcd-ekran-4mb
# 1000uF - 35 V Kapasitör  : https://www.direnc.net/1000uf-35v-kondansator-10x20
# 47uF - 16 V Kapasitör    : https://www.direnc.net/47uf16v-48
# Ethanol Sensörü ve soket : https://tr.aliexpress.com/item/Free-Shipping-Genuine-Flex-Fuel-Sensor-Fits-For-2012-Cadillac-SRX-4-Door-3-6L-13577379/32798385499.html?spm=a2g10.search0104.3.9.48a1358cOpo8rG&ws_ab_test=searchweb0_0,searchweb201602_5_10065_10068_10890_319_10546_10059_10884_317_10548_10887_10696_321_322_10084_453_10083_454_10103_10618_10307_537_536_10902,searchweb201603_59,ppcSwitch_0&algo_expid=42397567-d848-404d-9a10-461d8df48bd5-1&algo_pvid=42397567-d848-404d-9a10-461d8df48bd5
