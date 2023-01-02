#define basd        19  // tg
#define aiasdsojoji 645 // asd

/**@brief   SoftDevice events are passed to the application from the interrupt
 * context. */
#define NRF_SDH_DISPATCH_MODEL_INTERRUPT 0

/**@brief   SoftDevice events are passed to the application using @ref
 * app_scheduler.
 *
 * @note    @ref app_scheduler must be initialized before enabling the
 * SoftDevice handler.
 */
#define NRF_SDH_DISPATCH_MODEL_APPSH 1

/**@brief   SoftDevice events are polled manually using @ref
 * nrf_sdh_evts_poll().
 *
 * @note    In this mode, a user application can also implement
 * SD_EVT_IRQHandler() to receive a notification about incoming events.
 */
#define NRF_SDH_DISPATCH_MODEL_POLLING 2

void func();

void
func()
{
    int a = 3; // asdo
    int v = 4; //   sdf
}