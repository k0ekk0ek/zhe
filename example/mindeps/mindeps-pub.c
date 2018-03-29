#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "zhe.h"
#include "mindeps-platform.h"

#if defined(FREERTOS)
#include <FreeRTOS.h>
#include <task.h>
#endif /* FREERTOS */

#if defined(__IAR_SYSTEMS_ICC__)
#define fprintf(fh, ...) printf(__VA_ARGS__)
#endif /* __IAR_SYSTEMS_ICC__ */

void init_lwip(void);
void init_hardware(void);

/* NB this is pushing it: a hardcoded unique peer id ... */
static const uint8_t uniqueid[] = { 2 };

void pub(void *arg)
{
    init_lwip();

    struct zhe_platform * const platform = zhe_platform_new(PORT);
    struct zhe_config cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.id = uniqueid;
    cfg.idlen = sizeof(uniqueid);
    cfg.scoutaddr = (zhe_address_t *)&scoutaddr;
    if (!zhe_platform_join(platform, &scoutaddr)) {
        fprintf(stderr, "join scoutaddr failed\n");
        return;
    }
    if (zhe_init(&cfg, platform, zhe_platform_time()) < 0) {
        fprintf(stderr, "init failed\n");
        return;
    }
    zhe_start(zhe_platform_time());
    const zhe_pubidx_t p = zhe_publish(1, 0, true);
    uint64_t count = 0;
    zhe_time_t tlast = 0;
    while (true) {
        zhe_platform_background(platform);
        zhe_time_t tnow = zhe_platform_time();
        if (tnow / 1000 != tlast / 1000) {
            tlast = tnow;
            printf(">> Writing count %"PRIu64"\n", count);
            zhe_write(p, &count, (zhe_paysize_t)sizeof(count), tnow);
            count += 1;
        }
    }
}

int main()
{
    TaskHandle_t hdl;
    size_t sz = configMINIMAL_STACK_SIZE;

    init_hardware();

    xTaskCreate(&pub, "publisher", sz, NULL, (tskIDLE_PRIORITY + 2UL), &hdl);
    vTaskStartScheduler();

    return 0;
}
