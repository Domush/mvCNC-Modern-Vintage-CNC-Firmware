/**
 * Modern Vintage CNC Firmware
*/
#pragma once

#include "../inc/mvCNCConfig.h"

namespace DirectStepping {

  enum State : char {
    MONITOR, NEWLINE, ADDRESS, SIZE, COLLECT, CHECKSUM, UNFAIL
  };

  enum PageState : uint8_t {
    FREE, WRITING, OK, FAIL
  };

  // Static state used for stepping through direct stepping pages
  struct page_step_state_t {
    // Current page
    uint8_t *page;
    // Current segment
    uint16_t segment_idx;
    // Current steps within segment
    uint8_t segment_steps;
    // Segment delta
    xyze_uint8_t sd;
    // Block delta
    xyze_int_t bd;
  };

  template<typename Cfg>
  class SerialPageManager {
  public:

    typedef typename Cfg::page_idx_t page_idx_t;

    static bool maybe_store_rxd_char(uint8_t c);
    static void write_responses();

    // common methods for page managers
    static void init();
    static uint8_t *get_page(const page_idx_t page_idx);
    static void free_page(const page_idx_t page_idx);

  protected:

    typedef typename Cfg::write_byte_idx_t write_byte_idx_t;

    static State state;
    static volatile bool fatal_error;

    static volatile PageState page_states[Cfg::PAGE_COUNT];
    static volatile bool page_states_dirty;

    static uint8_t pages[Cfg::PAGE_COUNT][Cfg::PAGE_SIZE];
    static uint8_t checksum;
    static write_byte_idx_t write_byte_idx;
    static page_idx_t write_page_idx;
    static write_byte_idx_t write_page_size;

    static void set_page_state(const page_idx_t page_idx, const PageState page_state);
  };

  template<bool b, typename T, typename F> struct TypeSelector { typedef T type;} ;
  template<typename T, typename F> struct TypeSelector<false, T, F> { typedef F type; };

  template <int num_pages, int num_axes, int bits_segment, bool dir, int segments>
  struct config_t {
    static constexpr char CONTROL_CHAR  = '!';

    static constexpr int PAGE_COUNT     = num_pages;
    static constexpr int AXIS_COUNT     = num_axes;
    static constexpr int BITS_SEGMENT   = bits_segment;
    static constexpr int DIRECTIONAL    = dir ? 1 : 0;
    static constexpr int SEGMENTS       = segments;

    static constexpr int NUM_SEGMENTS   = _BV(BITS_SEGMENT);
    static constexpr int SEGMENT_STEPS  = _BV(BITS_SEGMENT - DIRECTIONAL) - 1;
    static constexpr int TOTAL_STEPS    = SEGMENT_STEPS * SEGMENTS;
    static constexpr int PAGE_SIZE      = (AXIS_COUNT * BITS_SEGMENT * SEGMENTS) / 8;

    typedef typename TypeSelector<(PAGE_SIZE>256), uint16_t, uint8_t>::type write_byte_idx_t;
    typedef typename TypeSelector<(PAGE_COUNT>256), uint16_t, uint8_t>::type page_idx_t;
  };

  template <uint8_t num_pages>
  using SP_4x4D_128 = config_t<num_pages, 4, 4, true,  128>;

  template <uint8_t num_pages>
  using SP_4x2_256  = config_t<num_pages, 4, 2, false, 256>;

  template <uint8_t num_pages>
  using SP_4x1_512  = config_t<num_pages, 4, 1, false, 512>;

  // configured types
  typedef STEPPER_PAGE_FORMAT<STEPPER_PAGES> Config;

  template class PAGE_MANAGER<Config>;
  typedef PAGE_MANAGER<Config> PageManager;
};

#define SP_4x4D_128 1
//#define SP_4x4_128 2
//#define SP_4x2D_256 3
#define SP_4x2_256 4
#define SP_4x1_512 5

typedef typename DirectStepping::Config::page_idx_t page_idx_t;

// TODO: use config
typedef DirectStepping::page_step_state_t page_step_state_t;

extern const uint8_t segment_table[DirectStepping::Config::NUM_SEGMENTS][DirectStepping::Config::SEGMENT_STEPS];
extern DirectStepping::PageManager page_manager;
