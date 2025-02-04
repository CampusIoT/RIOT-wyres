Ci-joint les 2 schemas. Mais, le rev C n’est pas à jour pour le RF switch, car dans la BOM finale, ils ont remplacer le SKY13350 par le SKY13453. C’est pin-compatible, sauf que le gpio de select est inversé…. (et je pense il n’y a qu’un neccessaire).
 
Dans le source, il y a ca dans hal_bsp.c :
```c
// BSP specific functions to set the radio antenna switch correctly
// For W_BASE card, 2 pins are ALWAYS required (revB or revC or later)
void BSP_antSwInit(int txPin, int rxPin) {
    assert(txPin!=-1);
    assert(rxPin!=-1);
    hal_gpio_init_out(txPin, 0);
    hal_gpio_init_out(rxPin, 0);
}
void BSP_antSwDeInit(int txPin, int rxPin) {
    assert(txPin!=-1);
    assert(rxPin!=-1);
    hal_gpio_deinit(txPin);
    hal_gpio_init_out(txPin, 0);
    hal_gpio_deinit(rxPin);
    hal_gpio_init_out(rxPin, 0);
}
void BSP_antSwTx(int txPin, int rxPin) {
    assert(txPin!=-1);
    assert(rxPin!=-1);
    if (BSP_getHwVer()<2) {     // proto or revB
        hal_gpio_write(txPin, 1);
        hal_gpio_write(rxPin, 0);
    } else {
        hal_gpio_write(txPin, 0);
        hal_gpio_write(rxPin, 1);
    }
}
void BSP_antSwRx(int txPin, int rxPin) {
    assert(txPin!=-1);
    assert(rxPin!=-1);
    if (BSP_getHwVer()<2) {     // proto or revB
        hal_gpio_write(txPin, 0);
        hal_gpio_write(rxPin, 1);
    } else {
        hal_gpio_write(txPin, 1);
        hal_gpio_write(rxPin, 1);
 
    }
}
```
 
Ces functions sont appeles depuis le sx1272-board.c dans le stack lorawan. Tu note que pour le rev C, le sens du ‘txPin’ est inversé vis-à-vis le rev B, et le rxPin n’est plus utilisé mais reste à 1…
 
