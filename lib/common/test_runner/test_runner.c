#include <common/test_runner/test_runner.h>
#include <common/log/log.h>
#include <common/timer/timer.h>
#include <rcc/rcc.h>
#include <addr_map.h>
#include <config.h>
#include <errors.h>
#include <common.h>

void main(void);

void run_test(void)
{

#ifdef CONFIG_COMMON_TEST_RUNNER
    int err;
    err = rcc_init();

#ifdef CONFIG_COMMON_LOGGER
    logger_init();
    pr_info("\n\n======= TEST RUNNER ========\n");
    if (err == SUCCESS) {
        pr_info("RCC successfully inited\n");
    }
    else {
        pr_info("RCC init failed: %u\n", err);
    }
    pr_info("Desired SYSCLK frequency: %uKHz\n", MHZ_TO_KHZ(SYSCLK_MHZ));
    pr_info("Actual  SYSCLK frequency: %uKHz\n", rcc_get_sysclk_freq_khz());
    pr_info("APB1 frequency:           %uKHz\n", rcc_get_apb1_freq_khz());
    pr_info("APB2 frequency:           %uKHz\n", rcc_get_apb2_freq_khz());
    pr_info("============================\n\n")

#endif

#ifdef CONFIG_COMMON_TIMER
    timer_init();
#endif

#endif

    main();
}
