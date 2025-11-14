#include <common/test_runner/test_runner.h>
#include <common/log/log.h>
#include <rcc/rcc.h>
#include <addr_map.h>
#include <config.h>

void main(void);

void run_test(void)
{

#ifdef CONFIG_COMMON_TEST_RUNNER
    prcc_t RCC = (prcc_t)RCC_BASE;
    rcc_init(RCC);

#ifdef CONFIG_COMMON_LOGGER
    logger_init();
#endif

#endif

    main();
}
