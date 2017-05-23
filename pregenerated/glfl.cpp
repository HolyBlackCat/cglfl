/*
  OpenGL Function Loader (GLFL) v1.1.1
  Copyright (C) 2017 Egor Mikhailov <blckcat@inbox.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "GLFL/glfl.h"
#include "GLFL/glfl_func_indices.h"

#include <iostream>

glfl::context *glfl::current_context = 0, *glfl::default_context = 0;

glfl::logging_function_t glfl::logging_function = [](const char *p){std::cout << p << '\n';};

unsigned long long glfl::draw_calls = 0;

bool glfl::check_errors = 0;
bool glfl::terminate_on_error = 0;
bool glfl::print_strings = 0;
bool glfl::disable_logging = 0;

namespace glfl_proxy
{
    int line = 0, prev_line = 0;
    const char *file = "";
    std::string prev_file = "";

    bool prev_check_errors = 0;
    bool prev_terminate_on_error = 0;
    bool prev_print_strings = 0;
    bool prev_disable_logging = 0;
}

void glfl::set_active_context(context *c)
{
    if (c == 0)
    {
        if (default_context == 0)
            default_context = new context;
        current_context = default_context;
    }
    else
        current_context = c;
}

void glfl::set_function_loader(function_loader_t ptr)
{
    if (current_context == 0)
        current_context = default_context = new context;
    current_context->function_loader = ptr;
    current_context->ptrs[0] = current_context->function_loader("meow");
}

void glfl::load_all_versions()
{
    load_gl();
    load_gles();
    load_glsc();
}

void glfl::load_everything()
{
    load_all_versions();
    load_extension_GL_3DFX_multisample();
    load_extension_GL_3DFX_tbuffer();
    load_extension_GL_3DFX_texture_compression_FXT1();
    load_extension_GL_AMD_blend_minmax_factor();
    load_extension_GL_AMD_compressed_3DC_texture();
    load_extension_GL_AMD_compressed_ATC_texture();
    load_extension_GL_AMD_conservative_depth();
    load_extension_GL_AMD_debug_output();
    load_extension_GL_AMD_depth_clamp_separate();
    load_extension_GL_AMD_draw_buffers_blend();
    load_extension_GL_AMD_framebuffer_sample_positions();
    load_extension_GL_AMD_gcn_shader();
    load_extension_GL_AMD_gpu_shader_half_float();
    load_extension_GL_AMD_gpu_shader_int64();
    load_extension_GL_AMD_interleaved_elements();
    load_extension_GL_AMD_multi_draw_indirect();
    load_extension_GL_AMD_name_gen_delete();
    load_extension_GL_AMD_occlusion_query_event();
    load_extension_GL_AMD_performance_monitor();
    load_extension_GL_AMD_pinned_memory();
    load_extension_GL_AMD_program_binary_Z400();
    load_extension_GL_AMD_query_buffer_object();
    load_extension_GL_AMD_sample_positions();
    load_extension_GL_AMD_seamless_cubemap_per_texture();
    load_extension_GL_AMD_shader_atomic_counter_ops();
    load_extension_GL_AMD_shader_ballot();
    load_extension_GL_AMD_shader_stencil_export();
    load_extension_GL_AMD_shader_trinary_minmax();
    load_extension_GL_AMD_shader_explicit_vertex_parameter();
    load_extension_GL_AMD_sparse_texture();
    load_extension_GL_AMD_stencil_operation_extended();
    load_extension_GL_AMD_texture_texture4();
    load_extension_GL_AMD_transform_feedback3_lines_triangles();
    load_extension_GL_AMD_transform_feedback4();
    load_extension_GL_AMD_vertex_shader_layer();
    load_extension_GL_AMD_vertex_shader_tessellator();
    load_extension_GL_AMD_vertex_shader_viewport_index();
    load_extension_GL_ANDROID_extension_pack_es31a();
    load_extension_GL_ANGLE_depth_texture();
    load_extension_GL_ANGLE_framebuffer_blit();
    load_extension_GL_ANGLE_framebuffer_multisample();
    load_extension_GL_ANGLE_instanced_arrays();
    load_extension_GL_ANGLE_pack_reverse_row_order();
    load_extension_GL_ANGLE_program_binary();
    load_extension_GL_ANGLE_texture_compression_dxt3();
    load_extension_GL_ANGLE_texture_compression_dxt5();
    load_extension_GL_ANGLE_texture_usage();
    load_extension_GL_ANGLE_translated_shader_source();
    load_extension_GL_APPLE_aux_depth_stencil();
    load_extension_GL_APPLE_client_storage();
    load_extension_GL_APPLE_clip_distance();
    load_extension_GL_APPLE_color_buffer_packed_float();
    load_extension_GL_APPLE_copy_texture_levels();
    load_extension_GL_APPLE_element_array();
    load_extension_GL_APPLE_fence();
    load_extension_GL_APPLE_float_pixels();
    load_extension_GL_APPLE_flush_buffer_range();
    load_extension_GL_APPLE_framebuffer_multisample();
    load_extension_GL_APPLE_object_purgeable();
    load_extension_GL_APPLE_rgb_422();
    load_extension_GL_APPLE_row_bytes();
    load_extension_GL_APPLE_specular_vector();
    load_extension_GL_APPLE_sync();
    load_extension_GL_APPLE_texture_2D_limited_npot();
    load_extension_GL_APPLE_texture_format_BGRA8888();
    load_extension_GL_APPLE_texture_max_level();
    load_extension_GL_APPLE_texture_packed_float();
    load_extension_GL_APPLE_texture_range();
    load_extension_GL_APPLE_transform_hint();
    load_extension_GL_APPLE_vertex_array_object();
    load_extension_GL_APPLE_vertex_array_range();
    load_extension_GL_APPLE_vertex_program_evaluators();
    load_extension_GL_APPLE_ycbcr_422();
    load_extension_GL_ARB_ES2_compatibility();
    load_extension_GL_ARB_ES3_1_compatibility();
    load_extension_GL_ARB_ES3_2_compatibility();
    load_extension_GL_ARB_ES3_compatibility();
    load_extension_GL_ARB_arrays_of_arrays();
    load_extension_GL_ARB_base_instance();
    load_extension_GL_ARB_bindless_texture();
    load_extension_GL_ARB_blend_func_extended();
    load_extension_GL_ARB_buffer_storage();
    load_extension_GL_ARB_cl_event();
    load_extension_GL_ARB_clear_buffer_object();
    load_extension_GL_ARB_clear_texture();
    load_extension_GL_ARB_clip_control();
    load_extension_GL_ARB_color_buffer_float();
    load_extension_GL_ARB_compatibility();
    load_extension_GL_ARB_compressed_texture_pixel_storage();
    load_extension_GL_ARB_compute_shader();
    load_extension_GL_ARB_compute_variable_group_size();
    load_extension_GL_ARB_conditional_render_inverted();
    load_extension_GL_ARB_conservative_depth();
    load_extension_GL_ARB_copy_buffer();
    load_extension_GL_ARB_copy_image();
    load_extension_GL_ARB_cull_distance();
    load_extension_GL_ARB_debug_output();
    load_extension_GL_ARB_depth_buffer_float();
    load_extension_GL_ARB_depth_clamp();
    load_extension_GL_ARB_depth_texture();
    load_extension_GL_ARB_derivative_control();
    load_extension_GL_ARB_direct_state_access();
    load_extension_GL_ARB_draw_buffers();
    load_extension_GL_ARB_draw_buffers_blend();
    load_extension_GL_ARB_draw_elements_base_vertex();
    load_extension_GL_ARB_draw_indirect();
    load_extension_GL_ARB_draw_instanced();
    load_extension_GL_ARB_enhanced_layouts();
    load_extension_GL_ARB_explicit_attrib_location();
    load_extension_GL_ARB_explicit_uniform_location();
    load_extension_GL_ARB_fragment_coord_conventions();
    load_extension_GL_ARB_fragment_layer_viewport();
    load_extension_GL_ARB_fragment_program();
    load_extension_GL_ARB_fragment_program_shadow();
    load_extension_GL_ARB_fragment_shader();
    load_extension_GL_ARB_fragment_shader_interlock();
    load_extension_GL_ARB_framebuffer_no_attachments();
    load_extension_GL_ARB_framebuffer_object();
    load_extension_GL_ARB_framebuffer_sRGB();
    load_extension_GL_ARB_geometry_shader4();
    load_extension_GL_ARB_get_program_binary();
    load_extension_GL_ARB_get_texture_sub_image();
    load_extension_GL_ARB_gpu_shader5();
    load_extension_GL_ARB_gpu_shader_fp64();
    load_extension_GL_ARB_gpu_shader_int64();
    load_extension_GL_ARB_half_float_pixel();
    load_extension_GL_ARB_half_float_vertex();
    load_extension_GL_ARB_imaging();
    load_extension_GL_ARB_indirect_parameters();
    load_extension_GL_ARB_instanced_arrays();
    load_extension_GL_ARB_internalformat_query();
    load_extension_GL_ARB_internalformat_query2();
    load_extension_GL_ARB_invalidate_subdata();
    load_extension_GL_ARB_map_buffer_alignment();
    load_extension_GL_ARB_map_buffer_range();
    load_extension_GL_ARB_matrix_palette();
    load_extension_GL_ARB_multi_bind();
    load_extension_GL_ARB_multi_draw_indirect();
    load_extension_GL_ARB_multisample();
    load_extension_GL_ARB_multitexture();
    load_extension_GL_ARB_occlusion_query();
    load_extension_GL_ARB_occlusion_query2();
    load_extension_GL_ARB_parallel_shader_compile();
    load_extension_GL_ARB_pipeline_statistics_query();
    load_extension_GL_ARB_pixel_buffer_object();
    load_extension_GL_ARB_point_parameters();
    load_extension_GL_ARB_point_sprite();
    load_extension_GL_ARB_post_depth_coverage();
    load_extension_GL_ARB_program_interface_query();
    load_extension_GL_ARB_provoking_vertex();
    load_extension_GL_ARB_query_buffer_object();
    load_extension_GL_ARB_robust_buffer_access_behavior();
    load_extension_GL_ARB_robustness();
    load_extension_GL_ARB_robustness_isolation();
    load_extension_GL_ARB_sample_locations();
    load_extension_GL_ARB_sample_shading();
    load_extension_GL_ARB_sampler_objects();
    load_extension_GL_ARB_seamless_cube_map();
    load_extension_GL_ARB_seamless_cubemap_per_texture();
    load_extension_GL_ARB_separate_shader_objects();
    load_extension_GL_ARB_shader_atomic_counter_ops();
    load_extension_GL_ARB_shader_atomic_counters();
    load_extension_GL_ARB_shader_ballot();
    load_extension_GL_ARB_shader_bit_encoding();
    load_extension_GL_ARB_shader_clock();
    load_extension_GL_ARB_shader_draw_parameters();
    load_extension_GL_ARB_shader_group_vote();
    load_extension_GL_ARB_shader_image_load_store();
    load_extension_GL_ARB_shader_image_size();
    load_extension_GL_ARB_shader_objects();
    load_extension_GL_ARB_shader_precision();
    load_extension_GL_ARB_shader_stencil_export();
    load_extension_GL_ARB_shader_storage_buffer_object();
    load_extension_GL_ARB_shader_subroutine();
    load_extension_GL_ARB_shader_texture_image_samples();
    load_extension_GL_ARB_shader_texture_lod();
    load_extension_GL_ARB_shader_viewport_layer_array();
    load_extension_GL_ARB_shading_language_100();
    load_extension_GL_ARB_shading_language_420pack();
    load_extension_GL_ARB_shading_language_include();
    load_extension_GL_ARB_shading_language_packing();
    load_extension_GL_ARB_shadow();
    load_extension_GL_ARB_shadow_ambient();
    load_extension_GL_ARB_sparse_buffer();
    load_extension_GL_ARB_sparse_texture();
    load_extension_GL_ARB_sparse_texture2();
    load_extension_GL_ARB_sparse_texture_clamp();
    load_extension_GL_ARB_stencil_texturing();
    load_extension_GL_ARB_sync();
    load_extension_GL_ARB_tessellation_shader();
    load_extension_GL_ARB_texture_barrier();
    load_extension_GL_ARB_texture_border_clamp();
    load_extension_GL_ARB_texture_buffer_object();
    load_extension_GL_ARB_texture_buffer_object_rgb32();
    load_extension_GL_ARB_texture_buffer_range();
    load_extension_GL_ARB_texture_compression();
    load_extension_GL_ARB_texture_compression_bptc();
    load_extension_GL_ARB_texture_compression_rgtc();
    load_extension_GL_ARB_texture_cube_map();
    load_extension_GL_ARB_texture_cube_map_array();
    load_extension_GL_ARB_texture_env_add();
    load_extension_GL_ARB_texture_env_combine();
    load_extension_GL_ARB_texture_env_crossbar();
    load_extension_GL_ARB_texture_env_dot3();
    load_extension_GL_ARB_texture_filter_minmax();
    load_extension_GL_ARB_texture_float();
    load_extension_GL_ARB_texture_gather();
    load_extension_GL_ARB_texture_mirror_clamp_to_edge();
    load_extension_GL_ARB_texture_mirrored_repeat();
    load_extension_GL_ARB_texture_multisample();
    load_extension_GL_ARB_texture_non_power_of_two();
    load_extension_GL_ARB_texture_query_levels();
    load_extension_GL_ARB_texture_query_lod();
    load_extension_GL_ARB_texture_rectangle();
    load_extension_GL_ARB_texture_rg();
    load_extension_GL_ARB_texture_rgb10_a2ui();
    load_extension_GL_ARB_texture_stencil8();
    load_extension_GL_ARB_texture_storage();
    load_extension_GL_ARB_texture_storage_multisample();
    load_extension_GL_ARB_texture_swizzle();
    load_extension_GL_ARB_texture_view();
    load_extension_GL_ARB_timer_query();
    load_extension_GL_ARB_transform_feedback2();
    load_extension_GL_ARB_transform_feedback3();
    load_extension_GL_ARB_transform_feedback_instanced();
    load_extension_GL_ARB_transform_feedback_overflow_query();
    load_extension_GL_ARB_transpose_matrix();
    load_extension_GL_ARB_uniform_buffer_object();
    load_extension_GL_ARB_vertex_array_bgra();
    load_extension_GL_ARB_vertex_array_object();
    load_extension_GL_ARB_vertex_attrib_64bit();
    load_extension_GL_ARB_vertex_attrib_binding();
    load_extension_GL_ARB_vertex_blend();
    load_extension_GL_ARB_vertex_buffer_object();
    load_extension_GL_ARB_vertex_program();
    load_extension_GL_ARB_vertex_shader();
    load_extension_GL_ARB_vertex_type_10f_11f_11f_rev();
    load_extension_GL_ARB_vertex_type_2_10_10_10_rev();
    load_extension_GL_ARB_viewport_array();
    load_extension_GL_ARB_window_pos();
    load_extension_GL_ARM_mali_program_binary();
    load_extension_GL_ARM_mali_shader_binary();
    load_extension_GL_ARM_rgba8();
    load_extension_GL_ARM_shader_framebuffer_fetch();
    load_extension_GL_ARM_shader_framebuffer_fetch_depth_stencil();
    load_extension_GL_ATI_draw_buffers();
    load_extension_GL_ATI_element_array();
    load_extension_GL_ATI_envmap_bumpmap();
    load_extension_GL_ATI_fragment_shader();
    load_extension_GL_ATI_map_object_buffer();
    load_extension_GL_ATI_meminfo();
    load_extension_GL_ATI_pixel_format_float();
    load_extension_GL_ATI_pn_triangles();
    load_extension_GL_ATI_separate_stencil();
    load_extension_GL_ATI_text_fragment_shader();
    load_extension_GL_ATI_texture_env_combine3();
    load_extension_GL_ATI_texture_float();
    load_extension_GL_ATI_texture_mirror_once();
    load_extension_GL_ATI_vertex_array_object();
    load_extension_GL_ATI_vertex_attrib_array_object();
    load_extension_GL_ATI_vertex_streams();
    load_extension_GL_DMP_program_binary();
    load_extension_GL_DMP_shader_binary();
    load_extension_GL_EXT_422_pixels();
    load_extension_GL_EXT_YUV_target();
    load_extension_GL_EXT_abgr();
    load_extension_GL_EXT_base_instance();
    load_extension_GL_EXT_bgra();
    load_extension_GL_EXT_bindable_uniform();
    load_extension_GL_EXT_blend_color();
    load_extension_GL_EXT_blend_equation_separate();
    load_extension_GL_EXT_blend_func_extended();
    load_extension_GL_EXT_blend_func_separate();
    load_extension_GL_EXT_blend_logic_op();
    load_extension_GL_EXT_blend_minmax();
    load_extension_GL_EXT_blend_subtract();
    load_extension_GL_EXT_buffer_storage();
    load_extension_GL_EXT_clear_texture();
    load_extension_GL_EXT_clip_cull_distance();
    load_extension_GL_EXT_clip_volume_hint();
    load_extension_GL_EXT_cmyka();
    load_extension_GL_EXT_color_buffer_float();
    load_extension_GL_EXT_color_buffer_half_float();
    load_extension_GL_EXT_color_subtable();
    load_extension_GL_EXT_compiled_vertex_array();
    load_extension_GL_EXT_conservative_depth();
    load_extension_GL_EXT_convolution();
    load_extension_GL_EXT_coordinate_frame();
    load_extension_GL_EXT_copy_image();
    load_extension_GL_EXT_copy_texture();
    load_extension_GL_EXT_cull_vertex();
    load_extension_GL_EXT_debug_label();
    load_extension_GL_EXT_debug_marker();
    load_extension_GL_EXT_depth_bounds_test();
    load_extension_GL_EXT_direct_state_access();
    load_extension_GL_EXT_discard_framebuffer();
    load_extension_GL_EXT_disjoint_timer_query();
    load_extension_GL_EXT_draw_buffers();
    load_extension_GL_EXT_draw_buffers2();
    load_extension_GL_EXT_draw_buffers_indexed();
    load_extension_GL_EXT_draw_elements_base_vertex();
    load_extension_GL_EXT_draw_instanced();
    load_extension_GL_EXT_draw_range_elements();
    load_extension_GL_EXT_draw_transform_feedback();
    load_extension_GL_EXT_float_blend();
    load_extension_GL_EXT_fog_coord();
    load_extension_GL_EXT_framebuffer_blit();
    load_extension_GL_EXT_framebuffer_multisample();
    load_extension_GL_EXT_framebuffer_multisample_blit_scaled();
    load_extension_GL_EXT_framebuffer_object();
    load_extension_GL_EXT_framebuffer_sRGB();
    load_extension_GL_EXT_geometry_point_size();
    load_extension_GL_EXT_geometry_shader();
    load_extension_GL_EXT_geometry_shader4();
    load_extension_GL_EXT_gpu_program_parameters();
    load_extension_GL_EXT_gpu_shader4();
    load_extension_GL_EXT_gpu_shader5();
    load_extension_GL_EXT_histogram();
    load_extension_GL_EXT_index_array_formats();
    load_extension_GL_EXT_index_func();
    load_extension_GL_EXT_index_material();
    load_extension_GL_EXT_index_texture();
    load_extension_GL_EXT_instanced_arrays();
    load_extension_GL_EXT_light_texture();
    load_extension_GL_EXT_map_buffer_range();
    load_extension_GL_EXT_misc_attribute();
    load_extension_GL_EXT_multi_draw_arrays();
    load_extension_GL_EXT_multi_draw_indirect();
    load_extension_GL_EXT_multisample();
    load_extension_GL_EXT_multisampled_compatibility();
    load_extension_GL_EXT_multisampled_render_to_texture();
    load_extension_GL_EXT_multiview_draw_buffers();
    load_extension_GL_EXT_occlusion_query_boolean();
    load_extension_GL_EXT_packed_depth_stencil();
    load_extension_GL_EXT_packed_float();
    load_extension_GL_EXT_packed_pixels();
    load_extension_GL_EXT_paletted_texture();
    load_extension_GL_EXT_pixel_buffer_object();
    load_extension_GL_EXT_pixel_transform();
    load_extension_GL_EXT_pixel_transform_color_table();
    load_extension_GL_EXT_point_parameters();
    load_extension_GL_EXT_polygon_offset();
    load_extension_GL_EXT_polygon_offset_clamp();
    load_extension_GL_EXT_post_depth_coverage();
    load_extension_GL_EXT_primitive_bounding_box();
    load_extension_GL_EXT_protected_textures();
    load_extension_GL_EXT_provoking_vertex();
    load_extension_GL_EXT_pvrtc_sRGB();
    load_extension_GL_EXT_raster_multisample();
    load_extension_GL_EXT_read_format_bgra();
    load_extension_GL_EXT_render_snorm();
    load_extension_GL_EXT_rescale_normal();
    load_extension_GL_EXT_robustness();
    load_extension_GL_EXT_sRGB();
    load_extension_GL_EXT_sRGB_write_control();
    load_extension_GL_EXT_secondary_color();
    load_extension_GL_EXT_separate_shader_objects();
    load_extension_GL_EXT_separate_specular_color();
    load_extension_GL_EXT_shader_framebuffer_fetch();
    load_extension_GL_EXT_shader_group_vote();
    load_extension_GL_EXT_shader_image_load_formatted();
    load_extension_GL_EXT_shader_image_load_store();
    load_extension_GL_EXT_shader_implicit_conversions();
    load_extension_GL_EXT_shader_integer_mix();
    load_extension_GL_EXT_shader_io_blocks();
    load_extension_GL_EXT_shader_non_constant_global_initializers();
    load_extension_GL_EXT_shader_pixel_local_storage();
    load_extension_GL_EXT_shader_pixel_local_storage2();
    load_extension_GL_EXT_shader_texture_lod();
    load_extension_GL_EXT_shadow_funcs();
    load_extension_GL_EXT_shadow_samplers();
    load_extension_GL_EXT_shared_texture_palette();
    load_extension_GL_EXT_sparse_texture();
    load_extension_GL_EXT_sparse_texture2();
    load_extension_GL_EXT_stencil_clear_tag();
    load_extension_GL_EXT_stencil_two_side();
    load_extension_GL_EXT_stencil_wrap();
    load_extension_GL_EXT_subtexture();
    load_extension_GL_EXT_tessellation_point_size();
    load_extension_GL_EXT_tessellation_shader();
    load_extension_GL_EXT_texture();
    load_extension_GL_EXT_texture3D();
    load_extension_GL_EXT_texture_array();
    load_extension_GL_EXT_texture_border_clamp();
    load_extension_GL_EXT_texture_buffer();
    load_extension_GL_EXT_texture_buffer_object();
    load_extension_GL_EXT_texture_compression_dxt1();
    load_extension_GL_EXT_texture_compression_latc();
    load_extension_GL_EXT_texture_compression_rgtc();
    load_extension_GL_EXT_texture_compression_s3tc();
    load_extension_GL_EXT_texture_cube_map();
    load_extension_GL_EXT_texture_cube_map_array();
    load_extension_GL_EXT_texture_env_add();
    load_extension_GL_EXT_texture_env_combine();
    load_extension_GL_EXT_texture_env_dot3();
    load_extension_GL_EXT_texture_filter_anisotropic();
    load_extension_GL_EXT_texture_filter_minmax();
    load_extension_GL_EXT_texture_format_BGRA8888();
    load_extension_GL_EXT_texture_integer();
    load_extension_GL_EXT_texture_lod_bias();
    load_extension_GL_EXT_texture_mirror_clamp();
    load_extension_GL_EXT_texture_norm16();
    load_extension_GL_EXT_texture_object();
    load_extension_GL_EXT_texture_perturb_normal();
    load_extension_GL_EXT_texture_rg();
    load_extension_GL_EXT_texture_sRGB();
    load_extension_GL_EXT_texture_sRGB_R8();
    load_extension_GL_EXT_texture_sRGB_RG8();
    load_extension_GL_EXT_texture_sRGB_decode();
    load_extension_GL_EXT_texture_shared_exponent();
    load_extension_GL_EXT_texture_snorm();
    load_extension_GL_EXT_texture_storage();
    load_extension_GL_EXT_texture_swizzle();
    load_extension_GL_EXT_texture_type_2_10_10_10_REV();
    load_extension_GL_EXT_texture_view();
    load_extension_GL_EXT_timer_query();
    load_extension_GL_EXT_transform_feedback();
    load_extension_GL_EXT_unpack_subimage();
    load_extension_GL_EXT_vertex_array();
    load_extension_GL_EXT_vertex_array_bgra();
    load_extension_GL_EXT_vertex_attrib_64bit();
    load_extension_GL_EXT_vertex_shader();
    load_extension_GL_EXT_vertex_weighting();
    load_extension_GL_EXT_window_rectangles();
    load_extension_GL_EXT_x11_sync_object();
    load_extension_GL_FJ_shader_binary_GCCSO();
    load_extension_GL_GREMEDY_frame_terminator();
    load_extension_GL_GREMEDY_string_marker();
    load_extension_GL_HP_convolution_border_modes();
    load_extension_GL_HP_image_transform();
    load_extension_GL_HP_occlusion_test();
    load_extension_GL_HP_texture_lighting();
    load_extension_GL_IBM_cull_vertex();
    load_extension_GL_IBM_multimode_draw_arrays();
    load_extension_GL_IBM_rasterpos_clip();
    load_extension_GL_IBM_static_data();
    load_extension_GL_IBM_texture_mirrored_repeat();
    load_extension_GL_IBM_vertex_array_lists();
    load_extension_GL_IMG_bindless_texture();
    load_extension_GL_IMG_framebuffer_downsample();
    load_extension_GL_IMG_multisampled_render_to_texture();
    load_extension_GL_IMG_program_binary();
    load_extension_GL_IMG_read_format();
    load_extension_GL_IMG_shader_binary();
    load_extension_GL_IMG_texture_compression_pvrtc();
    load_extension_GL_IMG_texture_compression_pvrtc2();
    load_extension_GL_IMG_texture_env_enhanced_fixed_function();
    load_extension_GL_IMG_texture_filter_cubic();
    load_extension_GL_IMG_user_clip_plane();
    load_extension_GL_INGR_blend_func_separate();
    load_extension_GL_INGR_color_clamp();
    load_extension_GL_INGR_interlace_read();
    load_extension_GL_INTEL_conservative_rasterization();
    load_extension_GL_INTEL_fragment_shader_ordering();
    load_extension_GL_INTEL_framebuffer_CMAA();
    load_extension_GL_INTEL_map_texture();
    load_extension_GL_INTEL_parallel_arrays();
    load_extension_GL_INTEL_performance_query();
    load_extension_GL_KHR_blend_equation_advanced();
    load_extension_GL_KHR_blend_equation_advanced_coherent();
    load_extension_GL_KHR_context_flush_control();
    load_extension_GL_KHR_debug();
    load_extension_GL_KHR_no_error();
    load_extension_GL_KHR_robust_buffer_access_behavior();
    load_extension_GL_KHR_robustness();
    load_extension_GL_KHR_texture_compression_astc_hdr();
    load_extension_GL_KHR_texture_compression_astc_ldr();
    load_extension_GL_KHR_texture_compression_astc_sliced_3d();
    load_extension_GL_MESAX_texture_stack();
    load_extension_GL_MESA_pack_invert();
    load_extension_GL_MESA_resize_buffers();
    load_extension_GL_MESA_window_pos();
    load_extension_GL_MESA_ycbcr_texture();
    load_extension_GL_NVX_conditional_render();
    load_extension_GL_NVX_gpu_memory_info();
    load_extension_GL_NV_bindless_multi_draw_indirect();
    load_extension_GL_NV_bindless_multi_draw_indirect_count();
    load_extension_GL_NV_bindless_texture();
    load_extension_GL_NV_blend_equation_advanced();
    load_extension_GL_NV_blend_equation_advanced_coherent();
    load_extension_GL_NV_blend_square();
    load_extension_GL_NV_clip_space_w_scaling();
    load_extension_GL_NV_command_list();
    load_extension_GL_NV_compute_program5();
    load_extension_GL_NV_conditional_render();
    load_extension_GL_NV_conservative_raster();
    load_extension_GL_NV_conservative_raster_dilate();
    load_extension_GL_NV_conservative_raster_pre_snap_triangles();
    load_extension_GL_NV_copy_buffer();
    load_extension_GL_NV_copy_depth_to_color();
    load_extension_GL_NV_copy_image();
    load_extension_GL_NV_coverage_sample();
    load_extension_GL_NV_deep_texture3D();
    load_extension_GL_NV_depth_buffer_float();
    load_extension_GL_NV_depth_clamp();
    load_extension_GL_NV_depth_nonlinear();
    load_extension_GL_NV_draw_buffers();
    load_extension_GL_NV_draw_instanced();
    load_extension_GL_NV_draw_texture();
    load_extension_GL_NV_evaluators();
    load_extension_GL_NV_explicit_attrib_location();
    load_extension_GL_NV_explicit_multisample();
    load_extension_GL_NV_fbo_color_attachments();
    load_extension_GL_NV_fence();
    load_extension_GL_NV_fill_rectangle();
    load_extension_GL_NV_float_buffer();
    load_extension_GL_NV_fog_distance();
    load_extension_GL_NV_fragment_coverage_to_color();
    load_extension_GL_NV_fragment_program();
    load_extension_GL_NV_fragment_program2();
    load_extension_GL_NV_fragment_program4();
    load_extension_GL_NV_fragment_program_option();
    load_extension_GL_NV_fragment_shader_interlock();
    load_extension_GL_NV_framebuffer_blit();
    load_extension_GL_NV_framebuffer_mixed_samples();
    load_extension_GL_NV_framebuffer_multisample();
    load_extension_GL_NV_framebuffer_multisample_coverage();
    load_extension_GL_NV_generate_mipmap_sRGB();
    load_extension_GL_NV_geometry_program4();
    load_extension_GL_NV_geometry_shader4();
    load_extension_GL_NV_geometry_shader_passthrough();
    load_extension_GL_NV_gpu_program4();
    load_extension_GL_NV_gpu_program5();
    load_extension_GL_NV_gpu_program5_mem_extended();
    load_extension_GL_NV_gpu_shader5();
    load_extension_GL_NV_half_float();
    load_extension_GL_NV_image_formats();
    load_extension_GL_NV_instanced_arrays();
    load_extension_GL_NV_internalformat_sample_query();
    load_extension_GL_NV_light_max_exponent();
    load_extension_GL_NV_multisample_coverage();
    load_extension_GL_NV_multisample_filter_hint();
    load_extension_GL_NV_non_square_matrices();
    load_extension_GL_NV_occlusion_query();
    load_extension_GL_NV_packed_depth_stencil();
    load_extension_GL_NV_parameter_buffer_object();
    load_extension_GL_NV_parameter_buffer_object2();
    load_extension_GL_NV_path_rendering();
    load_extension_GL_NV_path_rendering_shared_edge();
    load_extension_GL_NV_pixel_data_range();
    load_extension_GL_NV_point_sprite();
    load_extension_GL_NV_polygon_mode();
    load_extension_GL_NV_present_video();
    load_extension_GL_NV_primitive_restart();
    load_extension_GL_NV_read_buffer();
    load_extension_GL_NV_read_buffer_front();
    load_extension_GL_NV_read_depth();
    load_extension_GL_NV_read_depth_stencil();
    load_extension_GL_NV_read_stencil();
    load_extension_GL_NV_register_combiners();
    load_extension_GL_NV_register_combiners2();
    load_extension_GL_NV_robustness_video_memory_purge();
    load_extension_GL_NV_sRGB_formats();
    load_extension_GL_NV_sample_locations();
    load_extension_GL_NV_sample_mask_override_coverage();
    load_extension_GL_NV_shader_atomic_counters();
    load_extension_GL_NV_shader_atomic_float();
    load_extension_GL_NV_shader_atomic_float64();
    load_extension_GL_NV_shader_atomic_fp16_vector();
    load_extension_GL_NV_shader_atomic_int64();
    load_extension_GL_NV_shader_buffer_load();
    load_extension_GL_NV_shader_buffer_store();
    load_extension_GL_NV_shader_noperspective_interpolation();
    load_extension_GL_NV_shader_storage_buffer_object();
    load_extension_GL_NV_shader_thread_group();
    load_extension_GL_NV_shader_thread_shuffle();
    load_extension_GL_NV_shadow_samplers_array();
    load_extension_GL_NV_shadow_samplers_cube();
    load_extension_GL_NV_stereo_view_rendering();
    load_extension_GL_NV_tessellation_program5();
    load_extension_GL_NV_texgen_emboss();
    load_extension_GL_NV_texgen_reflection();
    load_extension_GL_NV_texture_barrier();
    load_extension_GL_NV_texture_border_clamp();
    load_extension_GL_NV_texture_compression_s3tc_update();
    load_extension_GL_NV_texture_compression_vtc();
    load_extension_GL_NV_texture_env_combine4();
    load_extension_GL_NV_texture_expand_normal();
    load_extension_GL_NV_texture_multisample();
    load_extension_GL_NV_texture_npot_2D_mipmap();
    load_extension_GL_NV_texture_rectangle();
    load_extension_GL_NV_texture_shader();
    load_extension_GL_NV_texture_shader2();
    load_extension_GL_NV_texture_shader3();
    load_extension_GL_NV_transform_feedback();
    load_extension_GL_NV_transform_feedback2();
    load_extension_GL_NV_uniform_buffer_unified_memory();
    load_extension_GL_NV_vdpau_interop();
    load_extension_GL_NV_vertex_array_range();
    load_extension_GL_NV_vertex_array_range2();
    load_extension_GL_NV_vertex_attrib_integer_64bit();
    load_extension_GL_NV_vertex_buffer_unified_memory();
    load_extension_GL_NV_vertex_program();
    load_extension_GL_NV_vertex_program1_1();
    load_extension_GL_NV_vertex_program2();
    load_extension_GL_NV_vertex_program2_option();
    load_extension_GL_NV_vertex_program3();
    load_extension_GL_NV_vertex_program4();
    load_extension_GL_NV_video_capture();
    load_extension_GL_NV_viewport_array();
    load_extension_GL_NV_viewport_array2();
    load_extension_GL_NV_viewport_swizzle();
    load_extension_GL_OES_EGL_image();
    load_extension_GL_OES_EGL_image_external();
    load_extension_GL_OES_EGL_image_external_essl3();
    load_extension_GL_OES_blend_equation_separate();
    load_extension_GL_OES_blend_func_separate();
    load_extension_GL_OES_blend_subtract();
    load_extension_GL_OES_byte_coordinates();
    load_extension_GL_OES_compressed_ETC1_RGB8_sub_texture();
    load_extension_GL_OES_compressed_ETC1_RGB8_texture();
    load_extension_GL_OES_compressed_paletted_texture();
    load_extension_GL_OES_copy_image();
    load_extension_GL_OES_depth24();
    load_extension_GL_OES_depth32();
    load_extension_GL_OES_depth_texture();
    load_extension_GL_OES_draw_buffers_indexed();
    load_extension_GL_OES_draw_elements_base_vertex();
    load_extension_GL_OES_draw_texture();
    load_extension_GL_OES_element_index_uint();
    load_extension_GL_OES_extended_matrix_palette();
    load_extension_GL_OES_fbo_render_mipmap();
    load_extension_GL_OES_fixed_point();
    load_extension_GL_OES_fragment_precision_high();
    load_extension_GL_OES_framebuffer_object();
    load_extension_GL_OES_geometry_point_size();
    load_extension_GL_OES_geometry_shader();
    load_extension_GL_OES_get_program_binary();
    load_extension_GL_OES_gpu_shader5();
    load_extension_GL_OES_mapbuffer();
    load_extension_GL_OES_matrix_get();
    load_extension_GL_OES_matrix_palette();
    load_extension_GL_OES_packed_depth_stencil();
    load_extension_GL_OES_point_size_array();
    load_extension_GL_OES_point_sprite();
    load_extension_GL_OES_primitive_bounding_box();
    load_extension_GL_OES_query_matrix();
    load_extension_GL_OES_read_format();
    load_extension_GL_OES_required_internalformat();
    load_extension_GL_OES_rgb8_rgba8();
    load_extension_GL_OES_sample_shading();
    load_extension_GL_OES_sample_variables();
    load_extension_GL_OES_shader_image_atomic();
    load_extension_GL_OES_shader_io_blocks();
    load_extension_GL_OES_shader_multisample_interpolation();
    load_extension_GL_OES_single_precision();
    load_extension_GL_OES_standard_derivatives();
    load_extension_GL_OES_stencil1();
    load_extension_GL_OES_stencil4();
    load_extension_GL_OES_stencil8();
    load_extension_GL_OES_stencil_wrap();
    load_extension_GL_OES_surfaceless_context();
    load_extension_GL_OES_tessellation_point_size();
    load_extension_GL_OES_tessellation_shader();
    load_extension_GL_OES_texture_3D();
    load_extension_GL_OES_texture_border_clamp();
    load_extension_GL_OES_texture_buffer();
    load_extension_GL_OES_texture_compression_astc();
    load_extension_GL_OES_texture_cube_map();
    load_extension_GL_OES_texture_cube_map_array();
    load_extension_GL_OES_texture_env_crossbar();
    load_extension_GL_OES_texture_float();
    load_extension_GL_OES_texture_float_linear();
    load_extension_GL_OES_texture_half_float();
    load_extension_GL_OES_texture_half_float_linear();
    load_extension_GL_OES_texture_mirrored_repeat();
    load_extension_GL_OES_texture_npot();
    load_extension_GL_OES_texture_stencil8();
    load_extension_GL_OES_texture_storage_multisample_2d_array();
    load_extension_GL_OES_texture_view();
    load_extension_GL_OES_vertex_array_object();
    load_extension_GL_OES_vertex_half_float();
    load_extension_GL_OES_vertex_type_10_10_10_2();
    load_extension_GL_OES_viewport_array();
    load_extension_GL_OML_interlace();
    load_extension_GL_OML_resample();
    load_extension_GL_OML_subsample();
    load_extension_GL_OVR_multiview();
    load_extension_GL_OVR_multiview2();
    load_extension_GL_OVR_multiview_multisampled_render_to_texture();
    load_extension_GL_PGI_misc_hints();
    load_extension_GL_PGI_vertex_hints();
    load_extension_GL_QCOM_alpha_test();
    load_extension_GL_QCOM_binning_control();
    load_extension_GL_QCOM_driver_control();
    load_extension_GL_QCOM_extended_get();
    load_extension_GL_QCOM_extended_get2();
    load_extension_GL_QCOM_perfmon_global_mode();
    load_extension_GL_QCOM_tiled_rendering();
    load_extension_GL_QCOM_writeonly_rendering();
    load_extension_GL_REND_screen_coordinates();
    load_extension_GL_S3_s3tc();
    load_extension_GL_SGIS_detail_texture();
    load_extension_GL_SGIS_fog_function();
    load_extension_GL_SGIS_generate_mipmap();
    load_extension_GL_SGIS_multisample();
    load_extension_GL_SGIS_pixel_texture();
    load_extension_GL_SGIS_point_line_texgen();
    load_extension_GL_SGIS_point_parameters();
    load_extension_GL_SGIS_sharpen_texture();
    load_extension_GL_SGIS_texture4D();
    load_extension_GL_SGIS_texture_border_clamp();
    load_extension_GL_SGIS_texture_color_mask();
    load_extension_GL_SGIS_texture_edge_clamp();
    load_extension_GL_SGIS_texture_filter4();
    load_extension_GL_SGIS_texture_lod();
    load_extension_GL_SGIS_texture_select();
    load_extension_GL_SGIX_async();
    load_extension_GL_SGIX_async_histogram();
    load_extension_GL_SGIX_async_pixel();
    load_extension_GL_SGIX_blend_alpha_minmax();
    load_extension_GL_SGIX_calligraphic_fragment();
    load_extension_GL_SGIX_clipmap();
    load_extension_GL_SGIX_convolution_accuracy();
    load_extension_GL_SGIX_depth_pass_instrument();
    load_extension_GL_SGIX_depth_texture();
    load_extension_GL_SGIX_flush_raster();
    load_extension_GL_SGIX_fog_offset();
    load_extension_GL_SGIX_fragment_lighting();
    load_extension_GL_SGIX_framezoom();
    load_extension_GL_SGIX_igloo_interface();
    load_extension_GL_SGIX_instruments();
    load_extension_GL_SGIX_interlace();
    load_extension_GL_SGIX_ir_instrument1();
    load_extension_GL_SGIX_list_priority();
    load_extension_GL_SGIX_pixel_texture();
    load_extension_GL_SGIX_pixel_tiles();
    load_extension_GL_SGIX_polynomial_ffd();
    load_extension_GL_SGIX_reference_plane();
    load_extension_GL_SGIX_resample();
    load_extension_GL_SGIX_scalebias_hint();
    load_extension_GL_SGIX_shadow();
    load_extension_GL_SGIX_shadow_ambient();
    load_extension_GL_SGIX_sprite();
    load_extension_GL_SGIX_subsample();
    load_extension_GL_SGIX_tag_sample_buffer();
    load_extension_GL_SGIX_texture_add_env();
    load_extension_GL_SGIX_texture_coordinate_clamp();
    load_extension_GL_SGIX_texture_lod_bias();
    load_extension_GL_SGIX_texture_multi_buffer();
    load_extension_GL_SGIX_texture_scale_bias();
    load_extension_GL_SGIX_vertex_preclip();
    load_extension_GL_SGIX_ycrcb();
    load_extension_GL_SGIX_ycrcb_subsample();
    load_extension_GL_SGIX_ycrcba();
    load_extension_GL_SGI_color_matrix();
    load_extension_GL_SGI_color_table();
    load_extension_GL_SGI_texture_color_table();
    load_extension_GL_SUNX_constant_data();
    load_extension_GL_SUN_convolution_border_modes();
    load_extension_GL_SUN_global_alpha();
    load_extension_GL_SUN_mesh_array();
    load_extension_GL_SUN_slice_accum();
    load_extension_GL_SUN_triangle_list();
    load_extension_GL_SUN_vertex();
    load_extension_GL_VIV_shader_binary();
    load_extension_GL_WIN_phong_shading();
    load_extension_GL_WIN_specular_fog();
}

#define GLFL_LOAD_FUNCTION(name) ((glfl::context *)(glfl::active_context()))->ptrs[glfl_func::name] = glfl::active_context()->function_loader("gl" #name);

static void load_version_gl(int major, int minor)
{
    major &= 0xffff;
    minor &= 0xffff;
    switch (0x10000 * major + minor)
    {
      default:
      [[fallthrough]];
      case 0x10000 * 4 + 5:
        GLFL_LOAD_FUNCTION(ClipControl);
        GLFL_LOAD_FUNCTION(CreateTransformFeedbacks);
        GLFL_LOAD_FUNCTION(TransformFeedbackBufferBase);
        GLFL_LOAD_FUNCTION(TransformFeedbackBufferRange);
        GLFL_LOAD_FUNCTION(GetTransformFeedbackiv);
        GLFL_LOAD_FUNCTION(GetTransformFeedbacki_v);
        GLFL_LOAD_FUNCTION(GetTransformFeedbacki64_v);
        GLFL_LOAD_FUNCTION(CreateBuffers);
        GLFL_LOAD_FUNCTION(NamedBufferStorage);
        GLFL_LOAD_FUNCTION(NamedBufferData);
        GLFL_LOAD_FUNCTION(NamedBufferSubData);
        GLFL_LOAD_FUNCTION(CopyNamedBufferSubData);
        GLFL_LOAD_FUNCTION(ClearNamedBufferData);
        GLFL_LOAD_FUNCTION(ClearNamedBufferSubData);
        GLFL_LOAD_FUNCTION(MapNamedBuffer);
        GLFL_LOAD_FUNCTION(MapNamedBufferRange);
        GLFL_LOAD_FUNCTION(UnmapNamedBuffer);
        GLFL_LOAD_FUNCTION(FlushMappedNamedBufferRange);
        GLFL_LOAD_FUNCTION(GetNamedBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetNamedBufferParameteri64v);
        GLFL_LOAD_FUNCTION(GetNamedBufferPointerv);
        GLFL_LOAD_FUNCTION(GetNamedBufferSubData);
        GLFL_LOAD_FUNCTION(CreateFramebuffers);
        GLFL_LOAD_FUNCTION(NamedFramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(NamedFramebufferParameteri);
        GLFL_LOAD_FUNCTION(NamedFramebufferTexture);
        GLFL_LOAD_FUNCTION(NamedFramebufferTextureLayer);
        GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffer);
        GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffers);
        GLFL_LOAD_FUNCTION(NamedFramebufferReadBuffer);
        GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferData);
        GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferSubData);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferiv);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferuiv);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferfv);
        GLFL_LOAD_FUNCTION(ClearNamedFramebufferfi);
        GLFL_LOAD_FUNCTION(BlitNamedFramebuffer);
        GLFL_LOAD_FUNCTION(CheckNamedFramebufferStatus);
        GLFL_LOAD_FUNCTION(GetNamedFramebufferParameteriv);
        GLFL_LOAD_FUNCTION(GetNamedFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(CreateRenderbuffers);
        GLFL_LOAD_FUNCTION(NamedRenderbufferStorage);
        GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisample);
        GLFL_LOAD_FUNCTION(GetNamedRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(CreateTextures);
        GLFL_LOAD_FUNCTION(TextureBuffer);
        GLFL_LOAD_FUNCTION(TextureBufferRange);
        GLFL_LOAD_FUNCTION(TextureStorage1D);
        GLFL_LOAD_FUNCTION(TextureStorage2D);
        GLFL_LOAD_FUNCTION(TextureStorage3D);
        GLFL_LOAD_FUNCTION(TextureStorage2DMultisample);
        GLFL_LOAD_FUNCTION(TextureStorage3DMultisample);
        GLFL_LOAD_FUNCTION(TextureSubImage1D);
        GLFL_LOAD_FUNCTION(TextureSubImage2D);
        GLFL_LOAD_FUNCTION(TextureSubImage3D);
        GLFL_LOAD_FUNCTION(CompressedTextureSubImage1D);
        GLFL_LOAD_FUNCTION(CompressedTextureSubImage2D);
        GLFL_LOAD_FUNCTION(CompressedTextureSubImage3D);
        GLFL_LOAD_FUNCTION(CopyTextureSubImage1D);
        GLFL_LOAD_FUNCTION(CopyTextureSubImage2D);
        GLFL_LOAD_FUNCTION(CopyTextureSubImage3D);
        GLFL_LOAD_FUNCTION(TextureParameterf);
        GLFL_LOAD_FUNCTION(TextureParameterfv);
        GLFL_LOAD_FUNCTION(TextureParameteri);
        GLFL_LOAD_FUNCTION(TextureParameterIiv);
        GLFL_LOAD_FUNCTION(TextureParameterIuiv);
        GLFL_LOAD_FUNCTION(TextureParameteriv);
        GLFL_LOAD_FUNCTION(GenerateTextureMipmap);
        GLFL_LOAD_FUNCTION(BindTextureUnit);
        GLFL_LOAD_FUNCTION(GetTextureImage);
        GLFL_LOAD_FUNCTION(GetCompressedTextureImage);
        GLFL_LOAD_FUNCTION(GetTextureLevelParameterfv);
        GLFL_LOAD_FUNCTION(GetTextureLevelParameteriv);
        GLFL_LOAD_FUNCTION(GetTextureParameterfv);
        GLFL_LOAD_FUNCTION(GetTextureParameterIiv);
        GLFL_LOAD_FUNCTION(GetTextureParameterIuiv);
        GLFL_LOAD_FUNCTION(GetTextureParameteriv);
        GLFL_LOAD_FUNCTION(CreateVertexArrays);
        GLFL_LOAD_FUNCTION(DisableVertexArrayAttrib);
        GLFL_LOAD_FUNCTION(EnableVertexArrayAttrib);
        GLFL_LOAD_FUNCTION(VertexArrayElementBuffer);
        GLFL_LOAD_FUNCTION(VertexArrayVertexBuffer);
        GLFL_LOAD_FUNCTION(VertexArrayVertexBuffers);
        GLFL_LOAD_FUNCTION(VertexArrayAttribBinding);
        GLFL_LOAD_FUNCTION(VertexArrayAttribFormat);
        GLFL_LOAD_FUNCTION(VertexArrayAttribIFormat);
        GLFL_LOAD_FUNCTION(VertexArrayAttribLFormat);
        GLFL_LOAD_FUNCTION(VertexArrayBindingDivisor);
        GLFL_LOAD_FUNCTION(GetVertexArrayiv);
        GLFL_LOAD_FUNCTION(GetVertexArrayIndexediv);
        GLFL_LOAD_FUNCTION(GetVertexArrayIndexed64iv);
        GLFL_LOAD_FUNCTION(CreateSamplers);
        GLFL_LOAD_FUNCTION(CreateProgramPipelines);
        GLFL_LOAD_FUNCTION(CreateQueries);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjecti64v);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjectiv);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjectui64v);
        GLFL_LOAD_FUNCTION(GetQueryBufferObjectuiv);
        GLFL_LOAD_FUNCTION(MemoryBarrierByRegion);
        GLFL_LOAD_FUNCTION(GetTextureSubImage);
        GLFL_LOAD_FUNCTION(GetCompressedTextureSubImage);
        GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
        GLFL_LOAD_FUNCTION(GetnCompressedTexImage);
        GLFL_LOAD_FUNCTION(GetnTexImage);
        GLFL_LOAD_FUNCTION(GetnUniformdv);
        GLFL_LOAD_FUNCTION(GetnUniformfv);
        GLFL_LOAD_FUNCTION(GetnUniformiv);
        GLFL_LOAD_FUNCTION(GetnUniformuiv);
        GLFL_LOAD_FUNCTION(ReadnPixels);
        GLFL_LOAD_FUNCTION(GetnMapdv);
        GLFL_LOAD_FUNCTION(GetnMapfv);
        GLFL_LOAD_FUNCTION(GetnMapiv);
        GLFL_LOAD_FUNCTION(GetnPixelMapfv);
        GLFL_LOAD_FUNCTION(GetnPixelMapuiv);
        GLFL_LOAD_FUNCTION(GetnPixelMapusv);
        GLFL_LOAD_FUNCTION(GetnPolygonStipple);
        GLFL_LOAD_FUNCTION(GetnColorTable);
        GLFL_LOAD_FUNCTION(GetnConvolutionFilter);
        GLFL_LOAD_FUNCTION(GetnSeparableFilter);
        GLFL_LOAD_FUNCTION(GetnHistogram);
        GLFL_LOAD_FUNCTION(GetnMinmax);
        GLFL_LOAD_FUNCTION(TextureBarrier);
      [[fallthrough]];
      case 0x10000 * 4 + 4:
        GLFL_LOAD_FUNCTION(BufferStorage);
        GLFL_LOAD_FUNCTION(ClearTexImage);
        GLFL_LOAD_FUNCTION(ClearTexSubImage);
        GLFL_LOAD_FUNCTION(BindBuffersBase);
        GLFL_LOAD_FUNCTION(BindBuffersRange);
        GLFL_LOAD_FUNCTION(BindTextures);
        GLFL_LOAD_FUNCTION(BindSamplers);
        GLFL_LOAD_FUNCTION(BindImageTextures);
        GLFL_LOAD_FUNCTION(BindVertexBuffers);
      [[fallthrough]];
      case 0x10000 * 4 + 3:
        GLFL_LOAD_FUNCTION(ClearBufferData);
        GLFL_LOAD_FUNCTION(ClearBufferSubData);
        GLFL_LOAD_FUNCTION(DispatchCompute);
        GLFL_LOAD_FUNCTION(DispatchComputeIndirect);
        GLFL_LOAD_FUNCTION(CopyImageSubData);
        GLFL_LOAD_FUNCTION(FramebufferParameteri);
        GLFL_LOAD_FUNCTION(GetFramebufferParameteriv);
        GLFL_LOAD_FUNCTION(GetInternalformati64v);
        GLFL_LOAD_FUNCTION(InvalidateTexSubImage);
        GLFL_LOAD_FUNCTION(InvalidateTexImage);
        GLFL_LOAD_FUNCTION(InvalidateBufferSubData);
        GLFL_LOAD_FUNCTION(InvalidateBufferData);
        GLFL_LOAD_FUNCTION(InvalidateFramebuffer);
        GLFL_LOAD_FUNCTION(InvalidateSubFramebuffer);
        GLFL_LOAD_FUNCTION(MultiDrawArraysIndirect);
        GLFL_LOAD_FUNCTION(MultiDrawElementsIndirect);
        GLFL_LOAD_FUNCTION(GetProgramInterfaceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceIndex);
        GLFL_LOAD_FUNCTION(GetProgramResourceName);
        GLFL_LOAD_FUNCTION(GetProgramResourceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceLocation);
        GLFL_LOAD_FUNCTION(GetProgramResourceLocationIndex);
        GLFL_LOAD_FUNCTION(ShaderStorageBlockBinding);
        GLFL_LOAD_FUNCTION(TexBufferRange);
        GLFL_LOAD_FUNCTION(TexStorage2DMultisample);
        GLFL_LOAD_FUNCTION(TexStorage3DMultisample);
        GLFL_LOAD_FUNCTION(TextureView);
        GLFL_LOAD_FUNCTION(BindVertexBuffer);
        GLFL_LOAD_FUNCTION(VertexAttribFormat);
        GLFL_LOAD_FUNCTION(VertexAttribIFormat);
        GLFL_LOAD_FUNCTION(VertexAttribLFormat);
        GLFL_LOAD_FUNCTION(VertexAttribBinding);
        GLFL_LOAD_FUNCTION(VertexBindingDivisor);
        GLFL_LOAD_FUNCTION(DebugMessageControl);
        GLFL_LOAD_FUNCTION(DebugMessageInsert);
        GLFL_LOAD_FUNCTION(DebugMessageCallback);
        GLFL_LOAD_FUNCTION(GetDebugMessageLog);
        GLFL_LOAD_FUNCTION(PushDebugGroup);
        GLFL_LOAD_FUNCTION(PopDebugGroup);
        GLFL_LOAD_FUNCTION(ObjectLabel);
        GLFL_LOAD_FUNCTION(GetObjectLabel);
        GLFL_LOAD_FUNCTION(ObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(GetPointerv);
      [[fallthrough]];
      case 0x10000 * 4 + 2:
        GLFL_LOAD_FUNCTION(DrawArraysInstancedBaseInstance);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseInstance);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexBaseInstance);
        GLFL_LOAD_FUNCTION(GetInternalformativ);
        GLFL_LOAD_FUNCTION(GetActiveAtomicCounterBufferiv);
        GLFL_LOAD_FUNCTION(BindImageTexture);
        GLFL_LOAD_FUNCTION(MemoryBarrier);
        GLFL_LOAD_FUNCTION(TexStorage1D);
        GLFL_LOAD_FUNCTION(TexStorage2D);
        GLFL_LOAD_FUNCTION(TexStorage3D);
        GLFL_LOAD_FUNCTION(DrawTransformFeedbackInstanced);
        GLFL_LOAD_FUNCTION(DrawTransformFeedbackStreamInstanced);
      [[fallthrough]];
      case 0x10000 * 4 + 1:
        GLFL_LOAD_FUNCTION(ReleaseShaderCompiler);
        GLFL_LOAD_FUNCTION(ShaderBinary);
        GLFL_LOAD_FUNCTION(GetShaderPrecisionFormat);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(GetProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramParameteri);
        GLFL_LOAD_FUNCTION(UseProgramStages);
        GLFL_LOAD_FUNCTION(ActiveShaderProgram);
        GLFL_LOAD_FUNCTION(CreateShaderProgramv);
        GLFL_LOAD_FUNCTION(BindProgramPipeline);
        GLFL_LOAD_FUNCTION(DeleteProgramPipelines);
        GLFL_LOAD_FUNCTION(GenProgramPipelines);
        GLFL_LOAD_FUNCTION(IsProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineiv);
        GLFL_LOAD_FUNCTION(ProgramUniform1i);
        GLFL_LOAD_FUNCTION(ProgramUniform1iv);
        GLFL_LOAD_FUNCTION(ProgramUniform1f);
        GLFL_LOAD_FUNCTION(ProgramUniform1fv);
        GLFL_LOAD_FUNCTION(ProgramUniform1d);
        GLFL_LOAD_FUNCTION(ProgramUniform1dv);
        GLFL_LOAD_FUNCTION(ProgramUniform1ui);
        GLFL_LOAD_FUNCTION(ProgramUniform1uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform2i);
        GLFL_LOAD_FUNCTION(ProgramUniform2iv);
        GLFL_LOAD_FUNCTION(ProgramUniform2f);
        GLFL_LOAD_FUNCTION(ProgramUniform2fv);
        GLFL_LOAD_FUNCTION(ProgramUniform2d);
        GLFL_LOAD_FUNCTION(ProgramUniform2dv);
        GLFL_LOAD_FUNCTION(ProgramUniform2ui);
        GLFL_LOAD_FUNCTION(ProgramUniform2uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform3i);
        GLFL_LOAD_FUNCTION(ProgramUniform3iv);
        GLFL_LOAD_FUNCTION(ProgramUniform3f);
        GLFL_LOAD_FUNCTION(ProgramUniform3fv);
        GLFL_LOAD_FUNCTION(ProgramUniform3d);
        GLFL_LOAD_FUNCTION(ProgramUniform3dv);
        GLFL_LOAD_FUNCTION(ProgramUniform3ui);
        GLFL_LOAD_FUNCTION(ProgramUniform3uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform4i);
        GLFL_LOAD_FUNCTION(ProgramUniform4iv);
        GLFL_LOAD_FUNCTION(ProgramUniform4f);
        GLFL_LOAD_FUNCTION(ProgramUniform4fv);
        GLFL_LOAD_FUNCTION(ProgramUniform4d);
        GLFL_LOAD_FUNCTION(ProgramUniform4dv);
        GLFL_LOAD_FUNCTION(ProgramUniform4ui);
        GLFL_LOAD_FUNCTION(ProgramUniform4uiv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4dv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3dv);
        GLFL_LOAD_FUNCTION(ValidateProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLog);
        GLFL_LOAD_FUNCTION(VertexAttribL1d);
        GLFL_LOAD_FUNCTION(VertexAttribL2d);
        GLFL_LOAD_FUNCTION(VertexAttribL3d);
        GLFL_LOAD_FUNCTION(VertexAttribL4d);
        GLFL_LOAD_FUNCTION(VertexAttribL1dv);
        GLFL_LOAD_FUNCTION(VertexAttribL2dv);
        GLFL_LOAD_FUNCTION(VertexAttribL3dv);
        GLFL_LOAD_FUNCTION(VertexAttribL4dv);
        GLFL_LOAD_FUNCTION(VertexAttribLPointer);
        GLFL_LOAD_FUNCTION(GetVertexAttribLdv);
        GLFL_LOAD_FUNCTION(ViewportArrayv);
        GLFL_LOAD_FUNCTION(ViewportIndexedf);
        GLFL_LOAD_FUNCTION(ViewportIndexedfv);
        GLFL_LOAD_FUNCTION(ScissorArrayv);
        GLFL_LOAD_FUNCTION(ScissorIndexed);
        GLFL_LOAD_FUNCTION(ScissorIndexedv);
        GLFL_LOAD_FUNCTION(DepthRangeArrayv);
        GLFL_LOAD_FUNCTION(DepthRangeIndexed);
        GLFL_LOAD_FUNCTION(GetFloati_v);
        GLFL_LOAD_FUNCTION(GetDoublei_v);
      [[fallthrough]];
      case 0x10000 * 4 + 0:
        GLFL_LOAD_FUNCTION(MinSampleShading);
        GLFL_LOAD_FUNCTION(BlendEquationi);
        GLFL_LOAD_FUNCTION(BlendEquationSeparatei);
        GLFL_LOAD_FUNCTION(BlendFunci);
        GLFL_LOAD_FUNCTION(BlendFuncSeparatei);
        GLFL_LOAD_FUNCTION(DrawArraysIndirect);
        GLFL_LOAD_FUNCTION(DrawElementsIndirect);
        GLFL_LOAD_FUNCTION(Uniform1d);
        GLFL_LOAD_FUNCTION(Uniform2d);
        GLFL_LOAD_FUNCTION(Uniform3d);
        GLFL_LOAD_FUNCTION(Uniform4d);
        GLFL_LOAD_FUNCTION(Uniform1dv);
        GLFL_LOAD_FUNCTION(Uniform2dv);
        GLFL_LOAD_FUNCTION(Uniform3dv);
        GLFL_LOAD_FUNCTION(Uniform4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix2dv);
        GLFL_LOAD_FUNCTION(UniformMatrix3dv);
        GLFL_LOAD_FUNCTION(UniformMatrix4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x3dv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x2dv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x4dv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x2dv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x3dv);
        GLFL_LOAD_FUNCTION(GetUniformdv);
        GLFL_LOAD_FUNCTION(GetSubroutineUniformLocation);
        GLFL_LOAD_FUNCTION(GetSubroutineIndex);
        GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformiv);
        GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformName);
        GLFL_LOAD_FUNCTION(GetActiveSubroutineName);
        GLFL_LOAD_FUNCTION(UniformSubroutinesuiv);
        GLFL_LOAD_FUNCTION(GetUniformSubroutineuiv);
        GLFL_LOAD_FUNCTION(GetProgramStageiv);
        GLFL_LOAD_FUNCTION(PatchParameteri);
        GLFL_LOAD_FUNCTION(PatchParameterfv);
        GLFL_LOAD_FUNCTION(BindTransformFeedback);
        GLFL_LOAD_FUNCTION(DeleteTransformFeedbacks);
        GLFL_LOAD_FUNCTION(GenTransformFeedbacks);
        GLFL_LOAD_FUNCTION(IsTransformFeedback);
        GLFL_LOAD_FUNCTION(PauseTransformFeedback);
        GLFL_LOAD_FUNCTION(ResumeTransformFeedback);
        GLFL_LOAD_FUNCTION(DrawTransformFeedback);
        GLFL_LOAD_FUNCTION(DrawTransformFeedbackStream);
        GLFL_LOAD_FUNCTION(BeginQueryIndexed);
        GLFL_LOAD_FUNCTION(EndQueryIndexed);
        GLFL_LOAD_FUNCTION(GetQueryIndexediv);
      [[fallthrough]];
      case 0x10000 * 3 + 3:
        GLFL_LOAD_FUNCTION(BindFragDataLocationIndexed);
        GLFL_LOAD_FUNCTION(GetFragDataIndex);
        GLFL_LOAD_FUNCTION(GenSamplers);
        GLFL_LOAD_FUNCTION(DeleteSamplers);
        GLFL_LOAD_FUNCTION(IsSampler);
        GLFL_LOAD_FUNCTION(BindSampler);
        GLFL_LOAD_FUNCTION(SamplerParameteri);
        GLFL_LOAD_FUNCTION(SamplerParameteriv);
        GLFL_LOAD_FUNCTION(SamplerParameterf);
        GLFL_LOAD_FUNCTION(SamplerParameterfv);
        GLFL_LOAD_FUNCTION(SamplerParameterIiv);
        GLFL_LOAD_FUNCTION(SamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameteriv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterfv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(QueryCounter);
        GLFL_LOAD_FUNCTION(GetQueryObjecti64v);
        GLFL_LOAD_FUNCTION(GetQueryObjectui64v);
        GLFL_LOAD_FUNCTION(VertexAttribDivisor);
        GLFL_LOAD_FUNCTION(VertexAttribP1ui);
        GLFL_LOAD_FUNCTION(VertexAttribP1uiv);
        GLFL_LOAD_FUNCTION(VertexAttribP2ui);
        GLFL_LOAD_FUNCTION(VertexAttribP2uiv);
        GLFL_LOAD_FUNCTION(VertexAttribP3ui);
        GLFL_LOAD_FUNCTION(VertexAttribP3uiv);
        GLFL_LOAD_FUNCTION(VertexAttribP4ui);
        GLFL_LOAD_FUNCTION(VertexAttribP4uiv);
        GLFL_LOAD_FUNCTION(VertexP2ui);
        GLFL_LOAD_FUNCTION(VertexP2uiv);
        GLFL_LOAD_FUNCTION(VertexP3ui);
        GLFL_LOAD_FUNCTION(VertexP3uiv);
        GLFL_LOAD_FUNCTION(VertexP4ui);
        GLFL_LOAD_FUNCTION(VertexP4uiv);
        GLFL_LOAD_FUNCTION(TexCoordP1ui);
        GLFL_LOAD_FUNCTION(TexCoordP1uiv);
        GLFL_LOAD_FUNCTION(TexCoordP2ui);
        GLFL_LOAD_FUNCTION(TexCoordP2uiv);
        GLFL_LOAD_FUNCTION(TexCoordP3ui);
        GLFL_LOAD_FUNCTION(TexCoordP3uiv);
        GLFL_LOAD_FUNCTION(TexCoordP4ui);
        GLFL_LOAD_FUNCTION(TexCoordP4uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP1ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP1uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP2ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP2uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP3ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP3uiv);
        GLFL_LOAD_FUNCTION(MultiTexCoordP4ui);
        GLFL_LOAD_FUNCTION(MultiTexCoordP4uiv);
        GLFL_LOAD_FUNCTION(NormalP3ui);
        GLFL_LOAD_FUNCTION(NormalP3uiv);
        GLFL_LOAD_FUNCTION(ColorP3ui);
        GLFL_LOAD_FUNCTION(ColorP3uiv);
        GLFL_LOAD_FUNCTION(ColorP4ui);
        GLFL_LOAD_FUNCTION(ColorP4uiv);
        GLFL_LOAD_FUNCTION(SecondaryColorP3ui);
        GLFL_LOAD_FUNCTION(SecondaryColorP3uiv);
      [[fallthrough]];
      case 0x10000 * 3 + 2:
        GLFL_LOAD_FUNCTION(DrawElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertex);
        GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertex);
        GLFL_LOAD_FUNCTION(ProvokingVertex);
        GLFL_LOAD_FUNCTION(FenceSync);
        GLFL_LOAD_FUNCTION(IsSync);
        GLFL_LOAD_FUNCTION(DeleteSync);
        GLFL_LOAD_FUNCTION(ClientWaitSync);
        GLFL_LOAD_FUNCTION(WaitSync);
        GLFL_LOAD_FUNCTION(GetInteger64v);
        GLFL_LOAD_FUNCTION(GetSynciv);
        GLFL_LOAD_FUNCTION(GetInteger64i_v);
        GLFL_LOAD_FUNCTION(GetBufferParameteri64v);
        GLFL_LOAD_FUNCTION(FramebufferTexture);
        GLFL_LOAD_FUNCTION(TexImage2DMultisample);
        GLFL_LOAD_FUNCTION(TexImage3DMultisample);
        GLFL_LOAD_FUNCTION(GetMultisamplefv);
        GLFL_LOAD_FUNCTION(SampleMaski);
      [[fallthrough]];
      case 0x10000 * 3 + 1:
        GLFL_LOAD_FUNCTION(DrawArraysInstanced);
        GLFL_LOAD_FUNCTION(DrawElementsInstanced);
        GLFL_LOAD_FUNCTION(TexBuffer);
        GLFL_LOAD_FUNCTION(PrimitiveRestartIndex);
        GLFL_LOAD_FUNCTION(CopyBufferSubData);
        GLFL_LOAD_FUNCTION(GetUniformIndices);
        GLFL_LOAD_FUNCTION(GetActiveUniformsiv);
        GLFL_LOAD_FUNCTION(GetActiveUniformName);
        GLFL_LOAD_FUNCTION(GetUniformBlockIndex);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockiv);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockName);
        GLFL_LOAD_FUNCTION(UniformBlockBinding);
        GLFL_LOAD_FUNCTION(BindBufferRange);
        GLFL_LOAD_FUNCTION(BindBufferBase);
        GLFL_LOAD_FUNCTION(GetIntegeri_v);
      [[fallthrough]];
      case 0x10000 * 3 + 0:
        GLFL_LOAD_FUNCTION(ColorMaski);
        GLFL_LOAD_FUNCTION(GetBooleani_v);
        GLFL_LOAD_FUNCTION(GetIntegeri_v);
        GLFL_LOAD_FUNCTION(Enablei);
        GLFL_LOAD_FUNCTION(Disablei);
        GLFL_LOAD_FUNCTION(IsEnabledi);
        GLFL_LOAD_FUNCTION(BeginTransformFeedback);
        GLFL_LOAD_FUNCTION(EndTransformFeedback);
        GLFL_LOAD_FUNCTION(BindBufferRange);
        GLFL_LOAD_FUNCTION(BindBufferBase);
        GLFL_LOAD_FUNCTION(TransformFeedbackVaryings);
        GLFL_LOAD_FUNCTION(GetTransformFeedbackVarying);
        GLFL_LOAD_FUNCTION(ClampColor);
        GLFL_LOAD_FUNCTION(BeginConditionalRender);
        GLFL_LOAD_FUNCTION(EndConditionalRender);
        GLFL_LOAD_FUNCTION(VertexAttribIPointer);
        GLFL_LOAD_FUNCTION(GetVertexAttribIiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribIuiv);
        GLFL_LOAD_FUNCTION(VertexAttribI1i);
        GLFL_LOAD_FUNCTION(VertexAttribI2i);
        GLFL_LOAD_FUNCTION(VertexAttribI3i);
        GLFL_LOAD_FUNCTION(VertexAttribI4i);
        GLFL_LOAD_FUNCTION(VertexAttribI1ui);
        GLFL_LOAD_FUNCTION(VertexAttribI2ui);
        GLFL_LOAD_FUNCTION(VertexAttribI3ui);
        GLFL_LOAD_FUNCTION(VertexAttribI4ui);
        GLFL_LOAD_FUNCTION(VertexAttribI1iv);
        GLFL_LOAD_FUNCTION(VertexAttribI2iv);
        GLFL_LOAD_FUNCTION(VertexAttribI3iv);
        GLFL_LOAD_FUNCTION(VertexAttribI4iv);
        GLFL_LOAD_FUNCTION(VertexAttribI1uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI2uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI3uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI4uiv);
        GLFL_LOAD_FUNCTION(VertexAttribI4bv);
        GLFL_LOAD_FUNCTION(VertexAttribI4sv);
        GLFL_LOAD_FUNCTION(VertexAttribI4ubv);
        GLFL_LOAD_FUNCTION(VertexAttribI4usv);
        GLFL_LOAD_FUNCTION(GetUniformuiv);
        GLFL_LOAD_FUNCTION(BindFragDataLocation);
        GLFL_LOAD_FUNCTION(GetFragDataLocation);
        GLFL_LOAD_FUNCTION(Uniform1ui);
        GLFL_LOAD_FUNCTION(Uniform2ui);
        GLFL_LOAD_FUNCTION(Uniform3ui);
        GLFL_LOAD_FUNCTION(Uniform4ui);
        GLFL_LOAD_FUNCTION(Uniform1uiv);
        GLFL_LOAD_FUNCTION(Uniform2uiv);
        GLFL_LOAD_FUNCTION(Uniform3uiv);
        GLFL_LOAD_FUNCTION(Uniform4uiv);
        GLFL_LOAD_FUNCTION(TexParameterIiv);
        GLFL_LOAD_FUNCTION(TexParameterIuiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIuiv);
        GLFL_LOAD_FUNCTION(ClearBufferiv);
        GLFL_LOAD_FUNCTION(ClearBufferuiv);
        GLFL_LOAD_FUNCTION(ClearBufferfv);
        GLFL_LOAD_FUNCTION(ClearBufferfi);
        GLFL_LOAD_FUNCTION(GetStringi);
        GLFL_LOAD_FUNCTION(IsRenderbuffer);
        GLFL_LOAD_FUNCTION(BindRenderbuffer);
        GLFL_LOAD_FUNCTION(DeleteRenderbuffers);
        GLFL_LOAD_FUNCTION(GenRenderbuffers);
        GLFL_LOAD_FUNCTION(RenderbufferStorage);
        GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(IsFramebuffer);
        GLFL_LOAD_FUNCTION(BindFramebuffer);
        GLFL_LOAD_FUNCTION(DeleteFramebuffers);
        GLFL_LOAD_FUNCTION(GenFramebuffers);
        GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
        GLFL_LOAD_FUNCTION(FramebufferTexture1D);
        GLFL_LOAD_FUNCTION(FramebufferTexture2D);
        GLFL_LOAD_FUNCTION(FramebufferTexture3D);
        GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(GenerateMipmap);
        GLFL_LOAD_FUNCTION(BlitFramebuffer);
        GLFL_LOAD_FUNCTION(RenderbufferStorageMultisample);
        GLFL_LOAD_FUNCTION(FramebufferTextureLayer);
        GLFL_LOAD_FUNCTION(MapBufferRange);
        GLFL_LOAD_FUNCTION(FlushMappedBufferRange);
        GLFL_LOAD_FUNCTION(BindVertexArray);
        GLFL_LOAD_FUNCTION(DeleteVertexArrays);
        GLFL_LOAD_FUNCTION(GenVertexArrays);
        GLFL_LOAD_FUNCTION(IsVertexArray);
      [[fallthrough]];
      case 0x10000 * 2 + 1:
        GLFL_LOAD_FUNCTION(UniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x3fv);
      [[fallthrough]];
      case 0x10000 * 2 + 0:
        GLFL_LOAD_FUNCTION(BlendEquationSeparate);
        GLFL_LOAD_FUNCTION(DrawBuffers);
        GLFL_LOAD_FUNCTION(StencilOpSeparate);
        GLFL_LOAD_FUNCTION(StencilFuncSeparate);
        GLFL_LOAD_FUNCTION(StencilMaskSeparate);
        GLFL_LOAD_FUNCTION(AttachShader);
        GLFL_LOAD_FUNCTION(BindAttribLocation);
        GLFL_LOAD_FUNCTION(CompileShader);
        GLFL_LOAD_FUNCTION(CreateProgram);
        GLFL_LOAD_FUNCTION(CreateShader);
        GLFL_LOAD_FUNCTION(DeleteProgram);
        GLFL_LOAD_FUNCTION(DeleteShader);
        GLFL_LOAD_FUNCTION(DetachShader);
        GLFL_LOAD_FUNCTION(DisableVertexAttribArray);
        GLFL_LOAD_FUNCTION(EnableVertexAttribArray);
        GLFL_LOAD_FUNCTION(GetActiveAttrib);
        GLFL_LOAD_FUNCTION(GetActiveUniform);
        GLFL_LOAD_FUNCTION(GetAttachedShaders);
        GLFL_LOAD_FUNCTION(GetAttribLocation);
        GLFL_LOAD_FUNCTION(GetProgramiv);
        GLFL_LOAD_FUNCTION(GetProgramInfoLog);
        GLFL_LOAD_FUNCTION(GetShaderiv);
        GLFL_LOAD_FUNCTION(GetShaderInfoLog);
        GLFL_LOAD_FUNCTION(GetShaderSource);
        GLFL_LOAD_FUNCTION(GetUniformLocation);
        GLFL_LOAD_FUNCTION(GetUniformfv);
        GLFL_LOAD_FUNCTION(GetUniformiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribdv);
        GLFL_LOAD_FUNCTION(GetVertexAttribfv);
        GLFL_LOAD_FUNCTION(GetVertexAttribiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribPointerv);
        GLFL_LOAD_FUNCTION(IsProgram);
        GLFL_LOAD_FUNCTION(IsShader);
        GLFL_LOAD_FUNCTION(LinkProgram);
        GLFL_LOAD_FUNCTION(ShaderSource);
        GLFL_LOAD_FUNCTION(UseProgram);
        GLFL_LOAD_FUNCTION(Uniform1f);
        GLFL_LOAD_FUNCTION(Uniform2f);
        GLFL_LOAD_FUNCTION(Uniform3f);
        GLFL_LOAD_FUNCTION(Uniform4f);
        GLFL_LOAD_FUNCTION(Uniform1i);
        GLFL_LOAD_FUNCTION(Uniform2i);
        GLFL_LOAD_FUNCTION(Uniform3i);
        GLFL_LOAD_FUNCTION(Uniform4i);
        GLFL_LOAD_FUNCTION(Uniform1fv);
        GLFL_LOAD_FUNCTION(Uniform2fv);
        GLFL_LOAD_FUNCTION(Uniform3fv);
        GLFL_LOAD_FUNCTION(Uniform4fv);
        GLFL_LOAD_FUNCTION(Uniform1iv);
        GLFL_LOAD_FUNCTION(Uniform2iv);
        GLFL_LOAD_FUNCTION(Uniform3iv);
        GLFL_LOAD_FUNCTION(Uniform4iv);
        GLFL_LOAD_FUNCTION(UniformMatrix2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4fv);
        GLFL_LOAD_FUNCTION(ValidateProgram);
        GLFL_LOAD_FUNCTION(VertexAttrib1d);
        GLFL_LOAD_FUNCTION(VertexAttrib1dv);
        GLFL_LOAD_FUNCTION(VertexAttrib1f);
        GLFL_LOAD_FUNCTION(VertexAttrib1fv);
        GLFL_LOAD_FUNCTION(VertexAttrib1s);
        GLFL_LOAD_FUNCTION(VertexAttrib1sv);
        GLFL_LOAD_FUNCTION(VertexAttrib2d);
        GLFL_LOAD_FUNCTION(VertexAttrib2dv);
        GLFL_LOAD_FUNCTION(VertexAttrib2f);
        GLFL_LOAD_FUNCTION(VertexAttrib2fv);
        GLFL_LOAD_FUNCTION(VertexAttrib2s);
        GLFL_LOAD_FUNCTION(VertexAttrib2sv);
        GLFL_LOAD_FUNCTION(VertexAttrib3d);
        GLFL_LOAD_FUNCTION(VertexAttrib3dv);
        GLFL_LOAD_FUNCTION(VertexAttrib3f);
        GLFL_LOAD_FUNCTION(VertexAttrib3fv);
        GLFL_LOAD_FUNCTION(VertexAttrib3s);
        GLFL_LOAD_FUNCTION(VertexAttrib3sv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nbv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Niv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nsv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nub);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nubv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nuiv);
        GLFL_LOAD_FUNCTION(VertexAttrib4Nusv);
        GLFL_LOAD_FUNCTION(VertexAttrib4bv);
        GLFL_LOAD_FUNCTION(VertexAttrib4d);
        GLFL_LOAD_FUNCTION(VertexAttrib4dv);
        GLFL_LOAD_FUNCTION(VertexAttrib4f);
        GLFL_LOAD_FUNCTION(VertexAttrib4fv);
        GLFL_LOAD_FUNCTION(VertexAttrib4iv);
        GLFL_LOAD_FUNCTION(VertexAttrib4s);
        GLFL_LOAD_FUNCTION(VertexAttrib4sv);
        GLFL_LOAD_FUNCTION(VertexAttrib4ubv);
        GLFL_LOAD_FUNCTION(VertexAttrib4uiv);
        GLFL_LOAD_FUNCTION(VertexAttrib4usv);
        GLFL_LOAD_FUNCTION(VertexAttribPointer);
      [[fallthrough]];
      case 0x10000 * 1 + 5:
        GLFL_LOAD_FUNCTION(GenQueries);
        GLFL_LOAD_FUNCTION(DeleteQueries);
        GLFL_LOAD_FUNCTION(IsQuery);
        GLFL_LOAD_FUNCTION(BeginQuery);
        GLFL_LOAD_FUNCTION(EndQuery);
        GLFL_LOAD_FUNCTION(GetQueryiv);
        GLFL_LOAD_FUNCTION(GetQueryObjectiv);
        GLFL_LOAD_FUNCTION(GetQueryObjectuiv);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(DeleteBuffers);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(IsBuffer);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(GetBufferSubData);
        GLFL_LOAD_FUNCTION(MapBuffer);
        GLFL_LOAD_FUNCTION(UnmapBuffer);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetBufferPointerv);
      [[fallthrough]];
      case 0x10000 * 1 + 4:
        GLFL_LOAD_FUNCTION(BlendFuncSeparate);
        GLFL_LOAD_FUNCTION(MultiDrawArrays);
        GLFL_LOAD_FUNCTION(MultiDrawElements);
        GLFL_LOAD_FUNCTION(PointParameterf);
        GLFL_LOAD_FUNCTION(PointParameterfv);
        GLFL_LOAD_FUNCTION(PointParameteri);
        GLFL_LOAD_FUNCTION(PointParameteriv);
        GLFL_LOAD_FUNCTION(FogCoordf);
        GLFL_LOAD_FUNCTION(FogCoordfv);
        GLFL_LOAD_FUNCTION(FogCoordd);
        GLFL_LOAD_FUNCTION(FogCoorddv);
        GLFL_LOAD_FUNCTION(FogCoordPointer);
        GLFL_LOAD_FUNCTION(SecondaryColor3b);
        GLFL_LOAD_FUNCTION(SecondaryColor3bv);
        GLFL_LOAD_FUNCTION(SecondaryColor3d);
        GLFL_LOAD_FUNCTION(SecondaryColor3dv);
        GLFL_LOAD_FUNCTION(SecondaryColor3f);
        GLFL_LOAD_FUNCTION(SecondaryColor3fv);
        GLFL_LOAD_FUNCTION(SecondaryColor3i);
        GLFL_LOAD_FUNCTION(SecondaryColor3iv);
        GLFL_LOAD_FUNCTION(SecondaryColor3s);
        GLFL_LOAD_FUNCTION(SecondaryColor3sv);
        GLFL_LOAD_FUNCTION(SecondaryColor3ub);
        GLFL_LOAD_FUNCTION(SecondaryColor3ubv);
        GLFL_LOAD_FUNCTION(SecondaryColor3ui);
        GLFL_LOAD_FUNCTION(SecondaryColor3uiv);
        GLFL_LOAD_FUNCTION(SecondaryColor3us);
        GLFL_LOAD_FUNCTION(SecondaryColor3usv);
        GLFL_LOAD_FUNCTION(SecondaryColorPointer);
        GLFL_LOAD_FUNCTION(WindowPos2d);
        GLFL_LOAD_FUNCTION(WindowPos2dv);
        GLFL_LOAD_FUNCTION(WindowPos2f);
        GLFL_LOAD_FUNCTION(WindowPos2fv);
        GLFL_LOAD_FUNCTION(WindowPos2i);
        GLFL_LOAD_FUNCTION(WindowPos2iv);
        GLFL_LOAD_FUNCTION(WindowPos2s);
        GLFL_LOAD_FUNCTION(WindowPos2sv);
        GLFL_LOAD_FUNCTION(WindowPos3d);
        GLFL_LOAD_FUNCTION(WindowPos3dv);
        GLFL_LOAD_FUNCTION(WindowPos3f);
        GLFL_LOAD_FUNCTION(WindowPos3fv);
        GLFL_LOAD_FUNCTION(WindowPos3i);
        GLFL_LOAD_FUNCTION(WindowPos3iv);
        GLFL_LOAD_FUNCTION(WindowPos3s);
        GLFL_LOAD_FUNCTION(WindowPos3sv);
        GLFL_LOAD_FUNCTION(BlendColor);
        GLFL_LOAD_FUNCTION(BlendEquation);
      [[fallthrough]];
      case 0x10000 * 1 + 3:
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(CompressedTexImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexImage1D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage1D);
        GLFL_LOAD_FUNCTION(GetCompressedTexImage);
        GLFL_LOAD_FUNCTION(ClientActiveTexture);
        GLFL_LOAD_FUNCTION(MultiTexCoord1d);
        GLFL_LOAD_FUNCTION(MultiTexCoord1dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord1f);
        GLFL_LOAD_FUNCTION(MultiTexCoord1fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord1i);
        GLFL_LOAD_FUNCTION(MultiTexCoord1iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord1s);
        GLFL_LOAD_FUNCTION(MultiTexCoord1sv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2d);
        GLFL_LOAD_FUNCTION(MultiTexCoord2dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2f);
        GLFL_LOAD_FUNCTION(MultiTexCoord2fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2i);
        GLFL_LOAD_FUNCTION(MultiTexCoord2iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord2s);
        GLFL_LOAD_FUNCTION(MultiTexCoord2sv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3d);
        GLFL_LOAD_FUNCTION(MultiTexCoord3dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3f);
        GLFL_LOAD_FUNCTION(MultiTexCoord3fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3i);
        GLFL_LOAD_FUNCTION(MultiTexCoord3iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord3s);
        GLFL_LOAD_FUNCTION(MultiTexCoord3sv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4d);
        GLFL_LOAD_FUNCTION(MultiTexCoord4dv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4f);
        GLFL_LOAD_FUNCTION(MultiTexCoord4fv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4i);
        GLFL_LOAD_FUNCTION(MultiTexCoord4iv);
        GLFL_LOAD_FUNCTION(MultiTexCoord4s);
        GLFL_LOAD_FUNCTION(MultiTexCoord4sv);
        GLFL_LOAD_FUNCTION(LoadTransposeMatrixf);
        GLFL_LOAD_FUNCTION(LoadTransposeMatrixd);
        GLFL_LOAD_FUNCTION(MultTransposeMatrixf);
        GLFL_LOAD_FUNCTION(MultTransposeMatrixd);
      [[fallthrough]];
      case 0x10000 * 1 + 2:
        GLFL_LOAD_FUNCTION(DrawRangeElements);
        GLFL_LOAD_FUNCTION(TexImage3D);
        GLFL_LOAD_FUNCTION(TexSubImage3D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage3D);
      [[fallthrough]];
      case 0x10000 * 1 + 1:
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawElements);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(CopyTexImage1D);
        GLFL_LOAD_FUNCTION(CopyTexImage2D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage1D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage2D);
        GLFL_LOAD_FUNCTION(TexSubImage1D);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(DeleteTextures);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(IsTexture);
        GLFL_LOAD_FUNCTION(ArrayElement);
        GLFL_LOAD_FUNCTION(ColorPointer);
        GLFL_LOAD_FUNCTION(DisableClientState);
        GLFL_LOAD_FUNCTION(EdgeFlagPointer);
        GLFL_LOAD_FUNCTION(EnableClientState);
        GLFL_LOAD_FUNCTION(IndexPointer);
        GLFL_LOAD_FUNCTION(InterleavedArrays);
        GLFL_LOAD_FUNCTION(NormalPointer);
        GLFL_LOAD_FUNCTION(TexCoordPointer);
        GLFL_LOAD_FUNCTION(VertexPointer);
        GLFL_LOAD_FUNCTION(AreTexturesResident);
        GLFL_LOAD_FUNCTION(PrioritizeTextures);
        GLFL_LOAD_FUNCTION(Indexub);
        GLFL_LOAD_FUNCTION(Indexubv);
        GLFL_LOAD_FUNCTION(PopClientAttrib);
        GLFL_LOAD_FUNCTION(PushClientAttrib);
      [[fallthrough]];
      case 0x10000 * 1 + 0:
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(PointSize);
        GLFL_LOAD_FUNCTION(PolygonMode);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexImage1D);
        GLFL_LOAD_FUNCTION(TexImage2D);
        GLFL_LOAD_FUNCTION(DrawBuffer);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ClearDepth);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(LogicOp);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(PixelStoref);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(ReadBuffer);
        GLFL_LOAD_FUNCTION(ReadPixels);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetDoublev);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexImage);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetTexLevelParameterfv);
        GLFL_LOAD_FUNCTION(GetTexLevelParameteriv);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(DepthRange);
        GLFL_LOAD_FUNCTION(Viewport);
        GLFL_LOAD_FUNCTION(NewList);
        GLFL_LOAD_FUNCTION(EndList);
        GLFL_LOAD_FUNCTION(CallList);
        GLFL_LOAD_FUNCTION(CallLists);
        GLFL_LOAD_FUNCTION(DeleteLists);
        GLFL_LOAD_FUNCTION(GenLists);
        GLFL_LOAD_FUNCTION(ListBase);
        GLFL_LOAD_FUNCTION(Begin);
        GLFL_LOAD_FUNCTION(Bitmap);
        GLFL_LOAD_FUNCTION(Color3b);
        GLFL_LOAD_FUNCTION(Color3bv);
        GLFL_LOAD_FUNCTION(Color3d);
        GLFL_LOAD_FUNCTION(Color3dv);
        GLFL_LOAD_FUNCTION(Color3f);
        GLFL_LOAD_FUNCTION(Color3fv);
        GLFL_LOAD_FUNCTION(Color3i);
        GLFL_LOAD_FUNCTION(Color3iv);
        GLFL_LOAD_FUNCTION(Color3s);
        GLFL_LOAD_FUNCTION(Color3sv);
        GLFL_LOAD_FUNCTION(Color3ub);
        GLFL_LOAD_FUNCTION(Color3ubv);
        GLFL_LOAD_FUNCTION(Color3ui);
        GLFL_LOAD_FUNCTION(Color3uiv);
        GLFL_LOAD_FUNCTION(Color3us);
        GLFL_LOAD_FUNCTION(Color3usv);
        GLFL_LOAD_FUNCTION(Color4b);
        GLFL_LOAD_FUNCTION(Color4bv);
        GLFL_LOAD_FUNCTION(Color4d);
        GLFL_LOAD_FUNCTION(Color4dv);
        GLFL_LOAD_FUNCTION(Color4f);
        GLFL_LOAD_FUNCTION(Color4fv);
        GLFL_LOAD_FUNCTION(Color4i);
        GLFL_LOAD_FUNCTION(Color4iv);
        GLFL_LOAD_FUNCTION(Color4s);
        GLFL_LOAD_FUNCTION(Color4sv);
        GLFL_LOAD_FUNCTION(Color4ub);
        GLFL_LOAD_FUNCTION(Color4ubv);
        GLFL_LOAD_FUNCTION(Color4ui);
        GLFL_LOAD_FUNCTION(Color4uiv);
        GLFL_LOAD_FUNCTION(Color4us);
        GLFL_LOAD_FUNCTION(Color4usv);
        GLFL_LOAD_FUNCTION(EdgeFlag);
        GLFL_LOAD_FUNCTION(EdgeFlagv);
        GLFL_LOAD_FUNCTION(End);
        GLFL_LOAD_FUNCTION(Indexd);
        GLFL_LOAD_FUNCTION(Indexdv);
        GLFL_LOAD_FUNCTION(Indexf);
        GLFL_LOAD_FUNCTION(Indexfv);
        GLFL_LOAD_FUNCTION(Indexi);
        GLFL_LOAD_FUNCTION(Indexiv);
        GLFL_LOAD_FUNCTION(Indexs);
        GLFL_LOAD_FUNCTION(Indexsv);
        GLFL_LOAD_FUNCTION(Normal3b);
        GLFL_LOAD_FUNCTION(Normal3bv);
        GLFL_LOAD_FUNCTION(Normal3d);
        GLFL_LOAD_FUNCTION(Normal3dv);
        GLFL_LOAD_FUNCTION(Normal3f);
        GLFL_LOAD_FUNCTION(Normal3fv);
        GLFL_LOAD_FUNCTION(Normal3i);
        GLFL_LOAD_FUNCTION(Normal3iv);
        GLFL_LOAD_FUNCTION(Normal3s);
        GLFL_LOAD_FUNCTION(Normal3sv);
        GLFL_LOAD_FUNCTION(RasterPos2d);
        GLFL_LOAD_FUNCTION(RasterPos2dv);
        GLFL_LOAD_FUNCTION(RasterPos2f);
        GLFL_LOAD_FUNCTION(RasterPos2fv);
        GLFL_LOAD_FUNCTION(RasterPos2i);
        GLFL_LOAD_FUNCTION(RasterPos2iv);
        GLFL_LOAD_FUNCTION(RasterPos2s);
        GLFL_LOAD_FUNCTION(RasterPos2sv);
        GLFL_LOAD_FUNCTION(RasterPos3d);
        GLFL_LOAD_FUNCTION(RasterPos3dv);
        GLFL_LOAD_FUNCTION(RasterPos3f);
        GLFL_LOAD_FUNCTION(RasterPos3fv);
        GLFL_LOAD_FUNCTION(RasterPos3i);
        GLFL_LOAD_FUNCTION(RasterPos3iv);
        GLFL_LOAD_FUNCTION(RasterPos3s);
        GLFL_LOAD_FUNCTION(RasterPos3sv);
        GLFL_LOAD_FUNCTION(RasterPos4d);
        GLFL_LOAD_FUNCTION(RasterPos4dv);
        GLFL_LOAD_FUNCTION(RasterPos4f);
        GLFL_LOAD_FUNCTION(RasterPos4fv);
        GLFL_LOAD_FUNCTION(RasterPos4i);
        GLFL_LOAD_FUNCTION(RasterPos4iv);
        GLFL_LOAD_FUNCTION(RasterPos4s);
        GLFL_LOAD_FUNCTION(RasterPos4sv);
        GLFL_LOAD_FUNCTION(Rectd);
        GLFL_LOAD_FUNCTION(Rectdv);
        GLFL_LOAD_FUNCTION(Rectf);
        GLFL_LOAD_FUNCTION(Rectfv);
        GLFL_LOAD_FUNCTION(Recti);
        GLFL_LOAD_FUNCTION(Rectiv);
        GLFL_LOAD_FUNCTION(Rects);
        GLFL_LOAD_FUNCTION(Rectsv);
        GLFL_LOAD_FUNCTION(TexCoord1d);
        GLFL_LOAD_FUNCTION(TexCoord1dv);
        GLFL_LOAD_FUNCTION(TexCoord1f);
        GLFL_LOAD_FUNCTION(TexCoord1fv);
        GLFL_LOAD_FUNCTION(TexCoord1i);
        GLFL_LOAD_FUNCTION(TexCoord1iv);
        GLFL_LOAD_FUNCTION(TexCoord1s);
        GLFL_LOAD_FUNCTION(TexCoord1sv);
        GLFL_LOAD_FUNCTION(TexCoord2d);
        GLFL_LOAD_FUNCTION(TexCoord2dv);
        GLFL_LOAD_FUNCTION(TexCoord2f);
        GLFL_LOAD_FUNCTION(TexCoord2fv);
        GLFL_LOAD_FUNCTION(TexCoord2i);
        GLFL_LOAD_FUNCTION(TexCoord2iv);
        GLFL_LOAD_FUNCTION(TexCoord2s);
        GLFL_LOAD_FUNCTION(TexCoord2sv);
        GLFL_LOAD_FUNCTION(TexCoord3d);
        GLFL_LOAD_FUNCTION(TexCoord3dv);
        GLFL_LOAD_FUNCTION(TexCoord3f);
        GLFL_LOAD_FUNCTION(TexCoord3fv);
        GLFL_LOAD_FUNCTION(TexCoord3i);
        GLFL_LOAD_FUNCTION(TexCoord3iv);
        GLFL_LOAD_FUNCTION(TexCoord3s);
        GLFL_LOAD_FUNCTION(TexCoord3sv);
        GLFL_LOAD_FUNCTION(TexCoord4d);
        GLFL_LOAD_FUNCTION(TexCoord4dv);
        GLFL_LOAD_FUNCTION(TexCoord4f);
        GLFL_LOAD_FUNCTION(TexCoord4fv);
        GLFL_LOAD_FUNCTION(TexCoord4i);
        GLFL_LOAD_FUNCTION(TexCoord4iv);
        GLFL_LOAD_FUNCTION(TexCoord4s);
        GLFL_LOAD_FUNCTION(TexCoord4sv);
        GLFL_LOAD_FUNCTION(Vertex2d);
        GLFL_LOAD_FUNCTION(Vertex2dv);
        GLFL_LOAD_FUNCTION(Vertex2f);
        GLFL_LOAD_FUNCTION(Vertex2fv);
        GLFL_LOAD_FUNCTION(Vertex2i);
        GLFL_LOAD_FUNCTION(Vertex2iv);
        GLFL_LOAD_FUNCTION(Vertex2s);
        GLFL_LOAD_FUNCTION(Vertex2sv);
        GLFL_LOAD_FUNCTION(Vertex3d);
        GLFL_LOAD_FUNCTION(Vertex3dv);
        GLFL_LOAD_FUNCTION(Vertex3f);
        GLFL_LOAD_FUNCTION(Vertex3fv);
        GLFL_LOAD_FUNCTION(Vertex3i);
        GLFL_LOAD_FUNCTION(Vertex3iv);
        GLFL_LOAD_FUNCTION(Vertex3s);
        GLFL_LOAD_FUNCTION(Vertex3sv);
        GLFL_LOAD_FUNCTION(Vertex4d);
        GLFL_LOAD_FUNCTION(Vertex4dv);
        GLFL_LOAD_FUNCTION(Vertex4f);
        GLFL_LOAD_FUNCTION(Vertex4fv);
        GLFL_LOAD_FUNCTION(Vertex4i);
        GLFL_LOAD_FUNCTION(Vertex4iv);
        GLFL_LOAD_FUNCTION(Vertex4s);
        GLFL_LOAD_FUNCTION(Vertex4sv);
        GLFL_LOAD_FUNCTION(ClipPlane);
        GLFL_LOAD_FUNCTION(ColorMaterial);
        GLFL_LOAD_FUNCTION(Fogf);
        GLFL_LOAD_FUNCTION(Fogfv);
        GLFL_LOAD_FUNCTION(Fogi);
        GLFL_LOAD_FUNCTION(Fogiv);
        GLFL_LOAD_FUNCTION(Lightf);
        GLFL_LOAD_FUNCTION(Lightfv);
        GLFL_LOAD_FUNCTION(Lighti);
        GLFL_LOAD_FUNCTION(Lightiv);
        GLFL_LOAD_FUNCTION(LightModelf);
        GLFL_LOAD_FUNCTION(LightModelfv);
        GLFL_LOAD_FUNCTION(LightModeli);
        GLFL_LOAD_FUNCTION(LightModeliv);
        GLFL_LOAD_FUNCTION(LineStipple);
        GLFL_LOAD_FUNCTION(Materialf);
        GLFL_LOAD_FUNCTION(Materialfv);
        GLFL_LOAD_FUNCTION(Materiali);
        GLFL_LOAD_FUNCTION(Materialiv);
        GLFL_LOAD_FUNCTION(PolygonStipple);
        GLFL_LOAD_FUNCTION(ShadeModel);
        GLFL_LOAD_FUNCTION(TexEnvf);
        GLFL_LOAD_FUNCTION(TexEnvfv);
        GLFL_LOAD_FUNCTION(TexEnvi);
        GLFL_LOAD_FUNCTION(TexEnviv);
        GLFL_LOAD_FUNCTION(TexGend);
        GLFL_LOAD_FUNCTION(TexGendv);
        GLFL_LOAD_FUNCTION(TexGenf);
        GLFL_LOAD_FUNCTION(TexGenfv);
        GLFL_LOAD_FUNCTION(TexGeni);
        GLFL_LOAD_FUNCTION(TexGeniv);
        GLFL_LOAD_FUNCTION(FeedbackBuffer);
        GLFL_LOAD_FUNCTION(SelectBuffer);
        GLFL_LOAD_FUNCTION(RenderMode);
        GLFL_LOAD_FUNCTION(InitNames);
        GLFL_LOAD_FUNCTION(LoadName);
        GLFL_LOAD_FUNCTION(PassThrough);
        GLFL_LOAD_FUNCTION(PopName);
        GLFL_LOAD_FUNCTION(PushName);
        GLFL_LOAD_FUNCTION(ClearAccum);
        GLFL_LOAD_FUNCTION(ClearIndex);
        GLFL_LOAD_FUNCTION(IndexMask);
        GLFL_LOAD_FUNCTION(Accum);
        GLFL_LOAD_FUNCTION(PopAttrib);
        GLFL_LOAD_FUNCTION(PushAttrib);
        GLFL_LOAD_FUNCTION(Map1d);
        GLFL_LOAD_FUNCTION(Map1f);
        GLFL_LOAD_FUNCTION(Map2d);
        GLFL_LOAD_FUNCTION(Map2f);
        GLFL_LOAD_FUNCTION(MapGrid1d);
        GLFL_LOAD_FUNCTION(MapGrid1f);
        GLFL_LOAD_FUNCTION(MapGrid2d);
        GLFL_LOAD_FUNCTION(MapGrid2f);
        GLFL_LOAD_FUNCTION(EvalCoord1d);
        GLFL_LOAD_FUNCTION(EvalCoord1dv);
        GLFL_LOAD_FUNCTION(EvalCoord1f);
        GLFL_LOAD_FUNCTION(EvalCoord1fv);
        GLFL_LOAD_FUNCTION(EvalCoord2d);
        GLFL_LOAD_FUNCTION(EvalCoord2dv);
        GLFL_LOAD_FUNCTION(EvalCoord2f);
        GLFL_LOAD_FUNCTION(EvalCoord2fv);
        GLFL_LOAD_FUNCTION(EvalMesh1);
        GLFL_LOAD_FUNCTION(EvalPoint1);
        GLFL_LOAD_FUNCTION(EvalMesh2);
        GLFL_LOAD_FUNCTION(EvalPoint2);
        GLFL_LOAD_FUNCTION(AlphaFunc);
        GLFL_LOAD_FUNCTION(PixelZoom);
        GLFL_LOAD_FUNCTION(PixelTransferf);
        GLFL_LOAD_FUNCTION(PixelTransferi);
        GLFL_LOAD_FUNCTION(PixelMapfv);
        GLFL_LOAD_FUNCTION(PixelMapuiv);
        GLFL_LOAD_FUNCTION(PixelMapusv);
        GLFL_LOAD_FUNCTION(CopyPixels);
        GLFL_LOAD_FUNCTION(DrawPixels);
        GLFL_LOAD_FUNCTION(GetClipPlane);
        GLFL_LOAD_FUNCTION(GetLightfv);
        GLFL_LOAD_FUNCTION(GetLightiv);
        GLFL_LOAD_FUNCTION(GetMapdv);
        GLFL_LOAD_FUNCTION(GetMapfv);
        GLFL_LOAD_FUNCTION(GetMapiv);
        GLFL_LOAD_FUNCTION(GetMaterialfv);
        GLFL_LOAD_FUNCTION(GetMaterialiv);
        GLFL_LOAD_FUNCTION(GetPixelMapfv);
        GLFL_LOAD_FUNCTION(GetPixelMapuiv);
        GLFL_LOAD_FUNCTION(GetPixelMapusv);
        GLFL_LOAD_FUNCTION(GetPolygonStipple);
        GLFL_LOAD_FUNCTION(GetTexEnvfv);
        GLFL_LOAD_FUNCTION(GetTexEnviv);
        GLFL_LOAD_FUNCTION(GetTexGendv);
        GLFL_LOAD_FUNCTION(GetTexGenfv);
        GLFL_LOAD_FUNCTION(GetTexGeniv);
        GLFL_LOAD_FUNCTION(IsList);
        GLFL_LOAD_FUNCTION(Frustum);
        GLFL_LOAD_FUNCTION(LoadIdentity);
        GLFL_LOAD_FUNCTION(LoadMatrixf);
        GLFL_LOAD_FUNCTION(LoadMatrixd);
        GLFL_LOAD_FUNCTION(MatrixMode);
        GLFL_LOAD_FUNCTION(MultMatrixf);
        GLFL_LOAD_FUNCTION(MultMatrixd);
        GLFL_LOAD_FUNCTION(Ortho);
        GLFL_LOAD_FUNCTION(PopMatrix);
        GLFL_LOAD_FUNCTION(PushMatrix);
        GLFL_LOAD_FUNCTION(Rotated);
        GLFL_LOAD_FUNCTION(Rotatef);
        GLFL_LOAD_FUNCTION(Scaled);
        GLFL_LOAD_FUNCTION(Scalef);
        GLFL_LOAD_FUNCTION(Translated);
        GLFL_LOAD_FUNCTION(Translatef);
    }
}
static void load_version_gles1(int major, int minor)
{
    major &= 0xffff;
    minor &= 0xffff;
    switch (0x10000 * major + minor)
    {
      default:
      [[fallthrough]];
      case 0x10000 * 1 + 0:
        GLFL_LOAD_FUNCTION(AlphaFunc);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(ClipPlanef);
        GLFL_LOAD_FUNCTION(Color4f);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(Fogf);
        GLFL_LOAD_FUNCTION(Fogfv);
        GLFL_LOAD_FUNCTION(Frustumf);
        GLFL_LOAD_FUNCTION(GetClipPlanef);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetLightfv);
        GLFL_LOAD_FUNCTION(GetMaterialfv);
        GLFL_LOAD_FUNCTION(GetTexEnvfv);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(LightModelf);
        GLFL_LOAD_FUNCTION(LightModelfv);
        GLFL_LOAD_FUNCTION(Lightf);
        GLFL_LOAD_FUNCTION(Lightfv);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(LoadMatrixf);
        GLFL_LOAD_FUNCTION(Materialf);
        GLFL_LOAD_FUNCTION(Materialfv);
        GLFL_LOAD_FUNCTION(MultMatrixf);
        GLFL_LOAD_FUNCTION(MultiTexCoord4f);
        GLFL_LOAD_FUNCTION(Normal3f);
        GLFL_LOAD_FUNCTION(Orthof);
        GLFL_LOAD_FUNCTION(PointParameterf);
        GLFL_LOAD_FUNCTION(PointParameterfv);
        GLFL_LOAD_FUNCTION(PointSize);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(Rotatef);
        GLFL_LOAD_FUNCTION(Scalef);
        GLFL_LOAD_FUNCTION(TexEnvf);
        GLFL_LOAD_FUNCTION(TexEnvfv);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(Translatef);
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(AlphaFuncx);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColorx);
        GLFL_LOAD_FUNCTION(ClearDepthx);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ClientActiveTexture);
        GLFL_LOAD_FUNCTION(ClipPlanex);
        GLFL_LOAD_FUNCTION(Color4ub);
        GLFL_LOAD_FUNCTION(Color4x);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(ColorPointer);
        GLFL_LOAD_FUNCTION(CompressedTexImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CopyTexImage2D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage2D);
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(DeleteBuffers);
        GLFL_LOAD_FUNCTION(DeleteTextures);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(DepthRangex);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(DisableClientState);
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawElements);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(EnableClientState);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(Fogx);
        GLFL_LOAD_FUNCTION(Fogxv);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(Frustumx);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetClipPlanex);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFixedv);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetLightxv);
        GLFL_LOAD_FUNCTION(GetMaterialxv);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexEnviv);
        GLFL_LOAD_FUNCTION(GetTexEnvxv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetTexParameterxv);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(IsBuffer);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(IsTexture);
        GLFL_LOAD_FUNCTION(LightModelx);
        GLFL_LOAD_FUNCTION(LightModelxv);
        GLFL_LOAD_FUNCTION(Lightx);
        GLFL_LOAD_FUNCTION(Lightxv);
        GLFL_LOAD_FUNCTION(LineWidthx);
        GLFL_LOAD_FUNCTION(LoadIdentity);
        GLFL_LOAD_FUNCTION(LoadMatrixx);
        GLFL_LOAD_FUNCTION(LogicOp);
        GLFL_LOAD_FUNCTION(Materialx);
        GLFL_LOAD_FUNCTION(Materialxv);
        GLFL_LOAD_FUNCTION(MatrixMode);
        GLFL_LOAD_FUNCTION(MultMatrixx);
        GLFL_LOAD_FUNCTION(MultiTexCoord4x);
        GLFL_LOAD_FUNCTION(Normal3x);
        GLFL_LOAD_FUNCTION(NormalPointer);
        GLFL_LOAD_FUNCTION(Orthox);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(PointParameterx);
        GLFL_LOAD_FUNCTION(PointParameterxv);
        GLFL_LOAD_FUNCTION(PointSizex);
        GLFL_LOAD_FUNCTION(PolygonOffsetx);
        GLFL_LOAD_FUNCTION(PopMatrix);
        GLFL_LOAD_FUNCTION(PushMatrix);
        GLFL_LOAD_FUNCTION(ReadPixels);
        GLFL_LOAD_FUNCTION(Rotatex);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(SampleCoveragex);
        GLFL_LOAD_FUNCTION(Scalex);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(ShadeModel);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(TexCoordPointer);
        GLFL_LOAD_FUNCTION(TexEnvi);
        GLFL_LOAD_FUNCTION(TexEnvx);
        GLFL_LOAD_FUNCTION(TexEnviv);
        GLFL_LOAD_FUNCTION(TexEnvxv);
        GLFL_LOAD_FUNCTION(TexImage2D);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameterx);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexParameterxv);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(Translatex);
        GLFL_LOAD_FUNCTION(VertexPointer);
        GLFL_LOAD_FUNCTION(Viewport);
    }
}
static void load_version_gles2(int major, int minor)
{
    major &= 0xffff;
    minor &= 0xffff;
    switch (0x10000 * major + minor)
    {
      default:
      [[fallthrough]];
      case 0x10000 * 3 + 2:
        GLFL_LOAD_FUNCTION(BlendBarrier);
        GLFL_LOAD_FUNCTION(CopyImageSubData);
        GLFL_LOAD_FUNCTION(DebugMessageControl);
        GLFL_LOAD_FUNCTION(DebugMessageInsert);
        GLFL_LOAD_FUNCTION(DebugMessageCallback);
        GLFL_LOAD_FUNCTION(GetDebugMessageLog);
        GLFL_LOAD_FUNCTION(PushDebugGroup);
        GLFL_LOAD_FUNCTION(PopDebugGroup);
        GLFL_LOAD_FUNCTION(ObjectLabel);
        GLFL_LOAD_FUNCTION(GetObjectLabel);
        GLFL_LOAD_FUNCTION(ObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetObjectPtrLabel);
        GLFL_LOAD_FUNCTION(GetPointerv);
        GLFL_LOAD_FUNCTION(Enablei);
        GLFL_LOAD_FUNCTION(Disablei);
        GLFL_LOAD_FUNCTION(BlendEquationi);
        GLFL_LOAD_FUNCTION(BlendEquationSeparatei);
        GLFL_LOAD_FUNCTION(BlendFunci);
        GLFL_LOAD_FUNCTION(BlendFuncSeparatei);
        GLFL_LOAD_FUNCTION(ColorMaski);
        GLFL_LOAD_FUNCTION(IsEnabledi);
        GLFL_LOAD_FUNCTION(DrawElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertex);
        GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertex);
        GLFL_LOAD_FUNCTION(FramebufferTexture);
        GLFL_LOAD_FUNCTION(PrimitiveBoundingBox);
        GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
        GLFL_LOAD_FUNCTION(ReadnPixels);
        GLFL_LOAD_FUNCTION(GetnUniformfv);
        GLFL_LOAD_FUNCTION(GetnUniformiv);
        GLFL_LOAD_FUNCTION(GetnUniformuiv);
        GLFL_LOAD_FUNCTION(MinSampleShading);
        GLFL_LOAD_FUNCTION(PatchParameteri);
        GLFL_LOAD_FUNCTION(TexParameterIiv);
        GLFL_LOAD_FUNCTION(TexParameterIuiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIiv);
        GLFL_LOAD_FUNCTION(GetTexParameterIuiv);
        GLFL_LOAD_FUNCTION(SamplerParameterIiv);
        GLFL_LOAD_FUNCTION(SamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIiv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterIuiv);
        GLFL_LOAD_FUNCTION(TexBuffer);
        GLFL_LOAD_FUNCTION(TexBufferRange);
        GLFL_LOAD_FUNCTION(TexStorage3DMultisample);
      [[fallthrough]];
      case 0x10000 * 3 + 1:
        GLFL_LOAD_FUNCTION(DispatchCompute);
        GLFL_LOAD_FUNCTION(DispatchComputeIndirect);
        GLFL_LOAD_FUNCTION(DrawArraysIndirect);
        GLFL_LOAD_FUNCTION(DrawElementsIndirect);
        GLFL_LOAD_FUNCTION(FramebufferParameteri);
        GLFL_LOAD_FUNCTION(GetFramebufferParameteriv);
        GLFL_LOAD_FUNCTION(GetProgramInterfaceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceIndex);
        GLFL_LOAD_FUNCTION(GetProgramResourceName);
        GLFL_LOAD_FUNCTION(GetProgramResourceiv);
        GLFL_LOAD_FUNCTION(GetProgramResourceLocation);
        GLFL_LOAD_FUNCTION(UseProgramStages);
        GLFL_LOAD_FUNCTION(ActiveShaderProgram);
        GLFL_LOAD_FUNCTION(CreateShaderProgramv);
        GLFL_LOAD_FUNCTION(BindProgramPipeline);
        GLFL_LOAD_FUNCTION(DeleteProgramPipelines);
        GLFL_LOAD_FUNCTION(GenProgramPipelines);
        GLFL_LOAD_FUNCTION(IsProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineiv);
        GLFL_LOAD_FUNCTION(ProgramUniform1i);
        GLFL_LOAD_FUNCTION(ProgramUniform2i);
        GLFL_LOAD_FUNCTION(ProgramUniform3i);
        GLFL_LOAD_FUNCTION(ProgramUniform4i);
        GLFL_LOAD_FUNCTION(ProgramUniform1ui);
        GLFL_LOAD_FUNCTION(ProgramUniform2ui);
        GLFL_LOAD_FUNCTION(ProgramUniform3ui);
        GLFL_LOAD_FUNCTION(ProgramUniform4ui);
        GLFL_LOAD_FUNCTION(ProgramUniform1f);
        GLFL_LOAD_FUNCTION(ProgramUniform2f);
        GLFL_LOAD_FUNCTION(ProgramUniform3f);
        GLFL_LOAD_FUNCTION(ProgramUniform4f);
        GLFL_LOAD_FUNCTION(ProgramUniform1iv);
        GLFL_LOAD_FUNCTION(ProgramUniform2iv);
        GLFL_LOAD_FUNCTION(ProgramUniform3iv);
        GLFL_LOAD_FUNCTION(ProgramUniform4iv);
        GLFL_LOAD_FUNCTION(ProgramUniform1uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform2uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform3uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform4uiv);
        GLFL_LOAD_FUNCTION(ProgramUniform1fv);
        GLFL_LOAD_FUNCTION(ProgramUniform2fv);
        GLFL_LOAD_FUNCTION(ProgramUniform3fv);
        GLFL_LOAD_FUNCTION(ProgramUniform4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fv);
        GLFL_LOAD_FUNCTION(ValidateProgramPipeline);
        GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLog);
        GLFL_LOAD_FUNCTION(BindImageTexture);
        GLFL_LOAD_FUNCTION(GetBooleani_v);
        GLFL_LOAD_FUNCTION(MemoryBarrier);
        GLFL_LOAD_FUNCTION(MemoryBarrierByRegion);
        GLFL_LOAD_FUNCTION(TexStorage2DMultisample);
        GLFL_LOAD_FUNCTION(GetMultisamplefv);
        GLFL_LOAD_FUNCTION(SampleMaski);
        GLFL_LOAD_FUNCTION(GetTexLevelParameteriv);
        GLFL_LOAD_FUNCTION(GetTexLevelParameterfv);
        GLFL_LOAD_FUNCTION(BindVertexBuffer);
        GLFL_LOAD_FUNCTION(VertexAttribFormat);
        GLFL_LOAD_FUNCTION(VertexAttribIFormat);
        GLFL_LOAD_FUNCTION(VertexAttribBinding);
        GLFL_LOAD_FUNCTION(VertexBindingDivisor);
      [[fallthrough]];
      case 0x10000 * 3 + 0:
        GLFL_LOAD_FUNCTION(ReadBuffer);
        GLFL_LOAD_FUNCTION(DrawRangeElements);
        GLFL_LOAD_FUNCTION(TexImage3D);
        GLFL_LOAD_FUNCTION(TexSubImage3D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexImage3D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage3D);
        GLFL_LOAD_FUNCTION(GenQueries);
        GLFL_LOAD_FUNCTION(DeleteQueries);
        GLFL_LOAD_FUNCTION(IsQuery);
        GLFL_LOAD_FUNCTION(BeginQuery);
        GLFL_LOAD_FUNCTION(EndQuery);
        GLFL_LOAD_FUNCTION(GetQueryiv);
        GLFL_LOAD_FUNCTION(GetQueryObjectuiv);
        GLFL_LOAD_FUNCTION(UnmapBuffer);
        GLFL_LOAD_FUNCTION(GetBufferPointerv);
        GLFL_LOAD_FUNCTION(DrawBuffers);
        GLFL_LOAD_FUNCTION(UniformMatrix2x3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix2x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3x4fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4x3fv);
        GLFL_LOAD_FUNCTION(BlitFramebuffer);
        GLFL_LOAD_FUNCTION(RenderbufferStorageMultisample);
        GLFL_LOAD_FUNCTION(FramebufferTextureLayer);
        GLFL_LOAD_FUNCTION(MapBufferRange);
        GLFL_LOAD_FUNCTION(FlushMappedBufferRange);
        GLFL_LOAD_FUNCTION(BindVertexArray);
        GLFL_LOAD_FUNCTION(DeleteVertexArrays);
        GLFL_LOAD_FUNCTION(GenVertexArrays);
        GLFL_LOAD_FUNCTION(IsVertexArray);
        GLFL_LOAD_FUNCTION(GetIntegeri_v);
        GLFL_LOAD_FUNCTION(BeginTransformFeedback);
        GLFL_LOAD_FUNCTION(EndTransformFeedback);
        GLFL_LOAD_FUNCTION(BindBufferRange);
        GLFL_LOAD_FUNCTION(BindBufferBase);
        GLFL_LOAD_FUNCTION(TransformFeedbackVaryings);
        GLFL_LOAD_FUNCTION(GetTransformFeedbackVarying);
        GLFL_LOAD_FUNCTION(VertexAttribIPointer);
        GLFL_LOAD_FUNCTION(GetVertexAttribIiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribIuiv);
        GLFL_LOAD_FUNCTION(VertexAttribI4i);
        GLFL_LOAD_FUNCTION(VertexAttribI4ui);
        GLFL_LOAD_FUNCTION(VertexAttribI4iv);
        GLFL_LOAD_FUNCTION(VertexAttribI4uiv);
        GLFL_LOAD_FUNCTION(GetUniformuiv);
        GLFL_LOAD_FUNCTION(GetFragDataLocation);
        GLFL_LOAD_FUNCTION(Uniform1ui);
        GLFL_LOAD_FUNCTION(Uniform2ui);
        GLFL_LOAD_FUNCTION(Uniform3ui);
        GLFL_LOAD_FUNCTION(Uniform4ui);
        GLFL_LOAD_FUNCTION(Uniform1uiv);
        GLFL_LOAD_FUNCTION(Uniform2uiv);
        GLFL_LOAD_FUNCTION(Uniform3uiv);
        GLFL_LOAD_FUNCTION(Uniform4uiv);
        GLFL_LOAD_FUNCTION(ClearBufferiv);
        GLFL_LOAD_FUNCTION(ClearBufferuiv);
        GLFL_LOAD_FUNCTION(ClearBufferfv);
        GLFL_LOAD_FUNCTION(ClearBufferfi);
        GLFL_LOAD_FUNCTION(GetStringi);
        GLFL_LOAD_FUNCTION(CopyBufferSubData);
        GLFL_LOAD_FUNCTION(GetUniformIndices);
        GLFL_LOAD_FUNCTION(GetActiveUniformsiv);
        GLFL_LOAD_FUNCTION(GetUniformBlockIndex);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockiv);
        GLFL_LOAD_FUNCTION(GetActiveUniformBlockName);
        GLFL_LOAD_FUNCTION(UniformBlockBinding);
        GLFL_LOAD_FUNCTION(DrawArraysInstanced);
        GLFL_LOAD_FUNCTION(DrawElementsInstanced);
        GLFL_LOAD_FUNCTION(FenceSync);
        GLFL_LOAD_FUNCTION(IsSync);
        GLFL_LOAD_FUNCTION(DeleteSync);
        GLFL_LOAD_FUNCTION(ClientWaitSync);
        GLFL_LOAD_FUNCTION(WaitSync);
        GLFL_LOAD_FUNCTION(GetInteger64v);
        GLFL_LOAD_FUNCTION(GetSynciv);
        GLFL_LOAD_FUNCTION(GetInteger64i_v);
        GLFL_LOAD_FUNCTION(GetBufferParameteri64v);
        GLFL_LOAD_FUNCTION(GenSamplers);
        GLFL_LOAD_FUNCTION(DeleteSamplers);
        GLFL_LOAD_FUNCTION(IsSampler);
        GLFL_LOAD_FUNCTION(BindSampler);
        GLFL_LOAD_FUNCTION(SamplerParameteri);
        GLFL_LOAD_FUNCTION(SamplerParameteriv);
        GLFL_LOAD_FUNCTION(SamplerParameterf);
        GLFL_LOAD_FUNCTION(SamplerParameterfv);
        GLFL_LOAD_FUNCTION(GetSamplerParameteriv);
        GLFL_LOAD_FUNCTION(GetSamplerParameterfv);
        GLFL_LOAD_FUNCTION(VertexAttribDivisor);
        GLFL_LOAD_FUNCTION(BindTransformFeedback);
        GLFL_LOAD_FUNCTION(DeleteTransformFeedbacks);
        GLFL_LOAD_FUNCTION(GenTransformFeedbacks);
        GLFL_LOAD_FUNCTION(IsTransformFeedback);
        GLFL_LOAD_FUNCTION(PauseTransformFeedback);
        GLFL_LOAD_FUNCTION(ResumeTransformFeedback);
        GLFL_LOAD_FUNCTION(GetProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramBinary);
        GLFL_LOAD_FUNCTION(ProgramParameteri);
        GLFL_LOAD_FUNCTION(InvalidateFramebuffer);
        GLFL_LOAD_FUNCTION(InvalidateSubFramebuffer);
        GLFL_LOAD_FUNCTION(TexStorage2D);
        GLFL_LOAD_FUNCTION(TexStorage3D);
        GLFL_LOAD_FUNCTION(GetInternalformativ);
      [[fallthrough]];
      case 0x10000 * 2 + 0:
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(AttachShader);
        GLFL_LOAD_FUNCTION(BindAttribLocation);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(BindFramebuffer);
        GLFL_LOAD_FUNCTION(BindRenderbuffer);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(BlendColor);
        GLFL_LOAD_FUNCTION(BlendEquation);
        GLFL_LOAD_FUNCTION(BlendEquationSeparate);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(BlendFuncSeparate);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(CompileShader);
        GLFL_LOAD_FUNCTION(CompressedTexImage2D);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CopyTexImage2D);
        GLFL_LOAD_FUNCTION(CopyTexSubImage2D);
        GLFL_LOAD_FUNCTION(CreateProgram);
        GLFL_LOAD_FUNCTION(CreateShader);
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(DeleteBuffers);
        GLFL_LOAD_FUNCTION(DeleteFramebuffers);
        GLFL_LOAD_FUNCTION(DeleteProgram);
        GLFL_LOAD_FUNCTION(DeleteRenderbuffers);
        GLFL_LOAD_FUNCTION(DeleteShader);
        GLFL_LOAD_FUNCTION(DeleteTextures);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(DetachShader);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(DisableVertexAttribArray);
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawElements);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(EnableVertexAttribArray);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(FramebufferTexture2D);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(GenerateMipmap);
        GLFL_LOAD_FUNCTION(GenFramebuffers);
        GLFL_LOAD_FUNCTION(GenRenderbuffers);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(GetActiveAttrib);
        GLFL_LOAD_FUNCTION(GetActiveUniform);
        GLFL_LOAD_FUNCTION(GetAttachedShaders);
        GLFL_LOAD_FUNCTION(GetAttribLocation);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetProgramiv);
        GLFL_LOAD_FUNCTION(GetProgramInfoLog);
        GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(GetShaderiv);
        GLFL_LOAD_FUNCTION(GetShaderInfoLog);
        GLFL_LOAD_FUNCTION(GetShaderPrecisionFormat);
        GLFL_LOAD_FUNCTION(GetShaderSource);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetUniformfv);
        GLFL_LOAD_FUNCTION(GetUniformiv);
        GLFL_LOAD_FUNCTION(GetUniformLocation);
        GLFL_LOAD_FUNCTION(GetVertexAttribfv);
        GLFL_LOAD_FUNCTION(GetVertexAttribiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribPointerv);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(IsBuffer);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(IsFramebuffer);
        GLFL_LOAD_FUNCTION(IsProgram);
        GLFL_LOAD_FUNCTION(IsRenderbuffer);
        GLFL_LOAD_FUNCTION(IsShader);
        GLFL_LOAD_FUNCTION(IsTexture);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(LinkProgram);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(ReadPixels);
        GLFL_LOAD_FUNCTION(ReleaseShaderCompiler);
        GLFL_LOAD_FUNCTION(RenderbufferStorage);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(ShaderBinary);
        GLFL_LOAD_FUNCTION(ShaderSource);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilFuncSeparate);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(StencilMaskSeparate);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(StencilOpSeparate);
        GLFL_LOAD_FUNCTION(TexImage2D);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(Uniform1f);
        GLFL_LOAD_FUNCTION(Uniform1fv);
        GLFL_LOAD_FUNCTION(Uniform1i);
        GLFL_LOAD_FUNCTION(Uniform1iv);
        GLFL_LOAD_FUNCTION(Uniform2f);
        GLFL_LOAD_FUNCTION(Uniform2fv);
        GLFL_LOAD_FUNCTION(Uniform2i);
        GLFL_LOAD_FUNCTION(Uniform2iv);
        GLFL_LOAD_FUNCTION(Uniform3f);
        GLFL_LOAD_FUNCTION(Uniform3fv);
        GLFL_LOAD_FUNCTION(Uniform3i);
        GLFL_LOAD_FUNCTION(Uniform3iv);
        GLFL_LOAD_FUNCTION(Uniform4f);
        GLFL_LOAD_FUNCTION(Uniform4fv);
        GLFL_LOAD_FUNCTION(Uniform4i);
        GLFL_LOAD_FUNCTION(Uniform4iv);
        GLFL_LOAD_FUNCTION(UniformMatrix2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4fv);
        GLFL_LOAD_FUNCTION(UseProgram);
        GLFL_LOAD_FUNCTION(ValidateProgram);
        GLFL_LOAD_FUNCTION(VertexAttrib1f);
        GLFL_LOAD_FUNCTION(VertexAttrib1fv);
        GLFL_LOAD_FUNCTION(VertexAttrib2f);
        GLFL_LOAD_FUNCTION(VertexAttrib2fv);
        GLFL_LOAD_FUNCTION(VertexAttrib3f);
        GLFL_LOAD_FUNCTION(VertexAttrib3fv);
        GLFL_LOAD_FUNCTION(VertexAttrib4f);
        GLFL_LOAD_FUNCTION(VertexAttrib4fv);
        GLFL_LOAD_FUNCTION(VertexAttribPointer);
        GLFL_LOAD_FUNCTION(Viewport);
    }
}
static void load_version_glsc2(int major, int minor)
{
    major &= 0xffff;
    minor &= 0xffff;
    switch (0x10000 * major + minor)
    {
      default:
      [[fallthrough]];
      case 0x10000 * 2 + 0:
        GLFL_LOAD_FUNCTION(ActiveTexture);
        GLFL_LOAD_FUNCTION(BindBuffer);
        GLFL_LOAD_FUNCTION(BindFramebuffer);
        GLFL_LOAD_FUNCTION(BindRenderbuffer);
        GLFL_LOAD_FUNCTION(BindTexture);
        GLFL_LOAD_FUNCTION(BlendColor);
        GLFL_LOAD_FUNCTION(BlendEquation);
        GLFL_LOAD_FUNCTION(BlendEquationSeparate);
        GLFL_LOAD_FUNCTION(BlendFunc);
        GLFL_LOAD_FUNCTION(BlendFuncSeparate);
        GLFL_LOAD_FUNCTION(BufferData);
        GLFL_LOAD_FUNCTION(BufferSubData);
        GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
        GLFL_LOAD_FUNCTION(Clear);
        GLFL_LOAD_FUNCTION(ClearColor);
        GLFL_LOAD_FUNCTION(ClearDepthf);
        GLFL_LOAD_FUNCTION(ClearStencil);
        GLFL_LOAD_FUNCTION(ColorMask);
        GLFL_LOAD_FUNCTION(CompressedTexSubImage2D);
        GLFL_LOAD_FUNCTION(CreateProgram);
        GLFL_LOAD_FUNCTION(CullFace);
        GLFL_LOAD_FUNCTION(DepthFunc);
        GLFL_LOAD_FUNCTION(DepthMask);
        GLFL_LOAD_FUNCTION(DepthRangef);
        GLFL_LOAD_FUNCTION(Disable);
        GLFL_LOAD_FUNCTION(DisableVertexAttribArray);
        GLFL_LOAD_FUNCTION(DrawArrays);
        GLFL_LOAD_FUNCTION(DrawRangeElements);
        GLFL_LOAD_FUNCTION(Enable);
        GLFL_LOAD_FUNCTION(EnableVertexAttribArray);
        GLFL_LOAD_FUNCTION(Finish);
        GLFL_LOAD_FUNCTION(Flush);
        GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
        GLFL_LOAD_FUNCTION(FramebufferTexture2D);
        GLFL_LOAD_FUNCTION(FrontFace);
        GLFL_LOAD_FUNCTION(GenBuffers);
        GLFL_LOAD_FUNCTION(GenerateMipmap);
        GLFL_LOAD_FUNCTION(GenFramebuffers);
        GLFL_LOAD_FUNCTION(GenRenderbuffers);
        GLFL_LOAD_FUNCTION(GenTextures);
        GLFL_LOAD_FUNCTION(GetAttribLocation);
        GLFL_LOAD_FUNCTION(GetBooleanv);
        GLFL_LOAD_FUNCTION(GetBufferParameteriv);
        GLFL_LOAD_FUNCTION(GetError);
        GLFL_LOAD_FUNCTION(GetFloatv);
        GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
        GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
        GLFL_LOAD_FUNCTION(GetIntegerv);
        GLFL_LOAD_FUNCTION(GetProgramiv);
        GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
        GLFL_LOAD_FUNCTION(GetString);
        GLFL_LOAD_FUNCTION(GetTexParameterfv);
        GLFL_LOAD_FUNCTION(GetTexParameteriv);
        GLFL_LOAD_FUNCTION(GetnUniformfv);
        GLFL_LOAD_FUNCTION(GetnUniformiv);
        GLFL_LOAD_FUNCTION(GetUniformLocation);
        GLFL_LOAD_FUNCTION(GetVertexAttribfv);
        GLFL_LOAD_FUNCTION(GetVertexAttribiv);
        GLFL_LOAD_FUNCTION(GetVertexAttribPointerv);
        GLFL_LOAD_FUNCTION(Hint);
        GLFL_LOAD_FUNCTION(IsEnabled);
        GLFL_LOAD_FUNCTION(LineWidth);
        GLFL_LOAD_FUNCTION(PixelStorei);
        GLFL_LOAD_FUNCTION(PolygonOffset);
        GLFL_LOAD_FUNCTION(ProgramBinary);
        GLFL_LOAD_FUNCTION(ReadnPixels);
        GLFL_LOAD_FUNCTION(RenderbufferStorage);
        GLFL_LOAD_FUNCTION(SampleCoverage);
        GLFL_LOAD_FUNCTION(Scissor);
        GLFL_LOAD_FUNCTION(StencilFunc);
        GLFL_LOAD_FUNCTION(StencilFuncSeparate);
        GLFL_LOAD_FUNCTION(StencilMask);
        GLFL_LOAD_FUNCTION(StencilMaskSeparate);
        GLFL_LOAD_FUNCTION(StencilOp);
        GLFL_LOAD_FUNCTION(StencilOpSeparate);
        GLFL_LOAD_FUNCTION(TexStorage2D);
        GLFL_LOAD_FUNCTION(TexParameterf);
        GLFL_LOAD_FUNCTION(TexParameterfv);
        GLFL_LOAD_FUNCTION(TexParameteri);
        GLFL_LOAD_FUNCTION(TexParameteriv);
        GLFL_LOAD_FUNCTION(TexSubImage2D);
        GLFL_LOAD_FUNCTION(Uniform1f);
        GLFL_LOAD_FUNCTION(Uniform1fv);
        GLFL_LOAD_FUNCTION(Uniform1i);
        GLFL_LOAD_FUNCTION(Uniform1iv);
        GLFL_LOAD_FUNCTION(Uniform2f);
        GLFL_LOAD_FUNCTION(Uniform2fv);
        GLFL_LOAD_FUNCTION(Uniform2i);
        GLFL_LOAD_FUNCTION(Uniform2iv);
        GLFL_LOAD_FUNCTION(Uniform3f);
        GLFL_LOAD_FUNCTION(Uniform3fv);
        GLFL_LOAD_FUNCTION(Uniform3i);
        GLFL_LOAD_FUNCTION(Uniform3iv);
        GLFL_LOAD_FUNCTION(Uniform4f);
        GLFL_LOAD_FUNCTION(Uniform4fv);
        GLFL_LOAD_FUNCTION(Uniform4i);
        GLFL_LOAD_FUNCTION(Uniform4iv);
        GLFL_LOAD_FUNCTION(UniformMatrix2fv);
        GLFL_LOAD_FUNCTION(UniformMatrix3fv);
        GLFL_LOAD_FUNCTION(UniformMatrix4fv);
        GLFL_LOAD_FUNCTION(UseProgram);
        GLFL_LOAD_FUNCTION(VertexAttrib1f);
        GLFL_LOAD_FUNCTION(VertexAttrib1fv);
        GLFL_LOAD_FUNCTION(VertexAttrib2f);
        GLFL_LOAD_FUNCTION(VertexAttrib2fv);
        GLFL_LOAD_FUNCTION(VertexAttrib3f);
        GLFL_LOAD_FUNCTION(VertexAttrib3fv);
        GLFL_LOAD_FUNCTION(VertexAttrib4f);
        GLFL_LOAD_FUNCTION(VertexAttrib4fv);
        GLFL_LOAD_FUNCTION(VertexAttribPointer);
        GLFL_LOAD_FUNCTION(Viewport);
    }
}

void glfl::load_gl(int major, int minor)
{
    load_version_gl(major, minor);
}
void glfl::load_gles(int major, int minor)
{
    if (major == 1 && minor == 0)
    {
        load_version_gles1(major, minor);
        return;
    }
    load_version_gles2(major, minor);
}
void glfl::load_glsc(int major, int minor)
{
    load_version_glsc2(major, minor);
}

void glfl::load_extension_GL_3DFX_multisample() {}
void glfl::load_extension_GL_3DFX_tbuffer()
{
    GLFL_LOAD_FUNCTION(TbufferMask3DFX);
}
void glfl::load_extension_GL_3DFX_texture_compression_FXT1() {}
void glfl::load_extension_GL_AMD_blend_minmax_factor() {}
void glfl::load_extension_GL_AMD_compressed_3DC_texture() {}
void glfl::load_extension_GL_AMD_compressed_ATC_texture() {}
void glfl::load_extension_GL_AMD_conservative_depth() {}
void glfl::load_extension_GL_AMD_debug_output()
{
    GLFL_LOAD_FUNCTION(DebugMessageEnableAMD);
    GLFL_LOAD_FUNCTION(DebugMessageInsertAMD);
    GLFL_LOAD_FUNCTION(DebugMessageCallbackAMD);
    GLFL_LOAD_FUNCTION(GetDebugMessageLogAMD);
}
void glfl::load_extension_GL_AMD_depth_clamp_separate() {}
void glfl::load_extension_GL_AMD_draw_buffers_blend()
{
    GLFL_LOAD_FUNCTION(BlendFuncIndexedAMD);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateIndexedAMD);
    GLFL_LOAD_FUNCTION(BlendEquationIndexedAMD);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateIndexedAMD);
}
void glfl::load_extension_GL_AMD_framebuffer_sample_positions()
{
    GLFL_LOAD_FUNCTION(FramebufferSamplePositionsfvAMD);
    GLFL_LOAD_FUNCTION(NamedFramebufferSamplePositionsfvAMD);
    GLFL_LOAD_FUNCTION(GetFramebufferParameterfvAMD);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferParameterfvAMD);
}
void glfl::load_extension_GL_AMD_gcn_shader() {}
void glfl::load_extension_GL_AMD_gpu_shader_half_float() {}
void glfl::load_extension_GL_AMD_gpu_shader_int64()
{
    GLFL_LOAD_FUNCTION(Uniform1i64NV);
    GLFL_LOAD_FUNCTION(Uniform2i64NV);
    GLFL_LOAD_FUNCTION(Uniform3i64NV);
    GLFL_LOAD_FUNCTION(Uniform4i64NV);
    GLFL_LOAD_FUNCTION(Uniform1i64vNV);
    GLFL_LOAD_FUNCTION(Uniform2i64vNV);
    GLFL_LOAD_FUNCTION(Uniform3i64vNV);
    GLFL_LOAD_FUNCTION(Uniform4i64vNV);
    GLFL_LOAD_FUNCTION(Uniform1ui64NV);
    GLFL_LOAD_FUNCTION(Uniform2ui64NV);
    GLFL_LOAD_FUNCTION(Uniform3ui64NV);
    GLFL_LOAD_FUNCTION(Uniform4ui64NV);
    GLFL_LOAD_FUNCTION(Uniform1ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform2ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform3ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform4ui64vNV);
    GLFL_LOAD_FUNCTION(GetUniformi64vNV);
    GLFL_LOAD_FUNCTION(GetUniformui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64vNV);
}
void glfl::load_extension_GL_AMD_interleaved_elements()
{
    GLFL_LOAD_FUNCTION(VertexAttribParameteriAMD);
}
void glfl::load_extension_GL_AMD_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectAMD);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectAMD);
}
void glfl::load_extension_GL_AMD_name_gen_delete()
{
    GLFL_LOAD_FUNCTION(GenNamesAMD);
    GLFL_LOAD_FUNCTION(DeleteNamesAMD);
    GLFL_LOAD_FUNCTION(IsNameAMD);
}
void glfl::load_extension_GL_AMD_occlusion_query_event()
{
    GLFL_LOAD_FUNCTION(QueryObjectParameteruiAMD);
}
void glfl::load_extension_GL_AMD_performance_monitor()
{
    GLFL_LOAD_FUNCTION(GetPerfMonitorGroupsAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCountersAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorGroupStringAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCounterStringAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCounterInfoAMD);
    GLFL_LOAD_FUNCTION(GenPerfMonitorsAMD);
    GLFL_LOAD_FUNCTION(DeletePerfMonitorsAMD);
    GLFL_LOAD_FUNCTION(SelectPerfMonitorCountersAMD);
    GLFL_LOAD_FUNCTION(BeginPerfMonitorAMD);
    GLFL_LOAD_FUNCTION(EndPerfMonitorAMD);
    GLFL_LOAD_FUNCTION(GetPerfMonitorCounterDataAMD);
}
void glfl::load_extension_GL_AMD_pinned_memory() {}
void glfl::load_extension_GL_AMD_program_binary_Z400() {}
void glfl::load_extension_GL_AMD_query_buffer_object() {}
void glfl::load_extension_GL_AMD_sample_positions()
{
    GLFL_LOAD_FUNCTION(SetMultisamplefvAMD);
}
void glfl::load_extension_GL_AMD_seamless_cubemap_per_texture() {}
void glfl::load_extension_GL_AMD_shader_atomic_counter_ops() {}
void glfl::load_extension_GL_AMD_shader_ballot() {}
void glfl::load_extension_GL_AMD_shader_stencil_export() {}
void glfl::load_extension_GL_AMD_shader_trinary_minmax() {}
void glfl::load_extension_GL_AMD_shader_explicit_vertex_parameter() {}
void glfl::load_extension_GL_AMD_sparse_texture()
{
    GLFL_LOAD_FUNCTION(TexStorageSparseAMD);
    GLFL_LOAD_FUNCTION(TextureStorageSparseAMD);
}
void glfl::load_extension_GL_AMD_stencil_operation_extended()
{
    GLFL_LOAD_FUNCTION(StencilOpValueAMD);
}
void glfl::load_extension_GL_AMD_texture_texture4() {}
void glfl::load_extension_GL_AMD_transform_feedback3_lines_triangles() {}
void glfl::load_extension_GL_AMD_transform_feedback4() {}
void glfl::load_extension_GL_AMD_vertex_shader_layer() {}
void glfl::load_extension_GL_AMD_vertex_shader_tessellator()
{
    GLFL_LOAD_FUNCTION(TessellationFactorAMD);
    GLFL_LOAD_FUNCTION(TessellationModeAMD);
}
void glfl::load_extension_GL_AMD_vertex_shader_viewport_index() {}
void glfl::load_extension_GL_ANDROID_extension_pack_es31a() {}
void glfl::load_extension_GL_ANGLE_depth_texture() {}
void glfl::load_extension_GL_ANGLE_framebuffer_blit()
{
    GLFL_LOAD_FUNCTION(BlitFramebufferANGLE);
}
void glfl::load_extension_GL_ANGLE_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleANGLE);
}
void glfl::load_extension_GL_ANGLE_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedANGLE);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedANGLE);
    GLFL_LOAD_FUNCTION(VertexAttribDivisorANGLE);
}
void glfl::load_extension_GL_ANGLE_pack_reverse_row_order() {}
void glfl::load_extension_GL_ANGLE_program_binary() {}
void glfl::load_extension_GL_ANGLE_texture_compression_dxt3() {}
void glfl::load_extension_GL_ANGLE_texture_compression_dxt5() {}
void glfl::load_extension_GL_ANGLE_texture_usage() {}
void glfl::load_extension_GL_ANGLE_translated_shader_source()
{
    GLFL_LOAD_FUNCTION(GetTranslatedShaderSourceANGLE);
}
void glfl::load_extension_GL_APPLE_aux_depth_stencil() {}
void glfl::load_extension_GL_APPLE_client_storage() {}
void glfl::load_extension_GL_APPLE_clip_distance() {}
void glfl::load_extension_GL_APPLE_color_buffer_packed_float() {}
void glfl::load_extension_GL_APPLE_copy_texture_levels()
{
    GLFL_LOAD_FUNCTION(CopyTextureLevelsAPPLE);
}
void glfl::load_extension_GL_APPLE_element_array()
{
    GLFL_LOAD_FUNCTION(ElementPointerAPPLE);
    GLFL_LOAD_FUNCTION(DrawElementArrayAPPLE);
    GLFL_LOAD_FUNCTION(DrawRangeElementArrayAPPLE);
    GLFL_LOAD_FUNCTION(MultiDrawElementArrayAPPLE);
    GLFL_LOAD_FUNCTION(MultiDrawRangeElementArrayAPPLE);
}
void glfl::load_extension_GL_APPLE_fence()
{
    GLFL_LOAD_FUNCTION(GenFencesAPPLE);
    GLFL_LOAD_FUNCTION(DeleteFencesAPPLE);
    GLFL_LOAD_FUNCTION(SetFenceAPPLE);
    GLFL_LOAD_FUNCTION(IsFenceAPPLE);
    GLFL_LOAD_FUNCTION(TestFenceAPPLE);
    GLFL_LOAD_FUNCTION(FinishFenceAPPLE);
    GLFL_LOAD_FUNCTION(TestObjectAPPLE);
    GLFL_LOAD_FUNCTION(FinishObjectAPPLE);
}
void glfl::load_extension_GL_APPLE_float_pixels() {}
void glfl::load_extension_GL_APPLE_flush_buffer_range()
{
    GLFL_LOAD_FUNCTION(BufferParameteriAPPLE);
    GLFL_LOAD_FUNCTION(FlushMappedBufferRangeAPPLE);
}
void glfl::load_extension_GL_APPLE_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleAPPLE);
    GLFL_LOAD_FUNCTION(ResolveMultisampleFramebufferAPPLE);
}
void glfl::load_extension_GL_APPLE_object_purgeable()
{
    GLFL_LOAD_FUNCTION(ObjectPurgeableAPPLE);
    GLFL_LOAD_FUNCTION(ObjectUnpurgeableAPPLE);
    GLFL_LOAD_FUNCTION(GetObjectParameterivAPPLE);
}
void glfl::load_extension_GL_APPLE_rgb_422() {}
void glfl::load_extension_GL_APPLE_row_bytes() {}
void glfl::load_extension_GL_APPLE_specular_vector() {}
void glfl::load_extension_GL_APPLE_sync()
{
    GLFL_LOAD_FUNCTION(FenceSyncAPPLE);
    GLFL_LOAD_FUNCTION(IsSyncAPPLE);
    GLFL_LOAD_FUNCTION(DeleteSyncAPPLE);
    GLFL_LOAD_FUNCTION(ClientWaitSyncAPPLE);
    GLFL_LOAD_FUNCTION(WaitSyncAPPLE);
    GLFL_LOAD_FUNCTION(GetInteger64vAPPLE);
    GLFL_LOAD_FUNCTION(GetSyncivAPPLE);
}
void glfl::load_extension_GL_APPLE_texture_2D_limited_npot() {}
void glfl::load_extension_GL_APPLE_texture_format_BGRA8888() {}
void glfl::load_extension_GL_APPLE_texture_max_level() {}
void glfl::load_extension_GL_APPLE_texture_packed_float() {}
void glfl::load_extension_GL_APPLE_texture_range()
{
    GLFL_LOAD_FUNCTION(TextureRangeAPPLE);
    GLFL_LOAD_FUNCTION(GetTexParameterPointervAPPLE);
}
void glfl::load_extension_GL_APPLE_transform_hint() {}
void glfl::load_extension_GL_APPLE_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(BindVertexArrayAPPLE);
    GLFL_LOAD_FUNCTION(DeleteVertexArraysAPPLE);
    GLFL_LOAD_FUNCTION(GenVertexArraysAPPLE);
    GLFL_LOAD_FUNCTION(IsVertexArrayAPPLE);
}
void glfl::load_extension_GL_APPLE_vertex_array_range()
{
    GLFL_LOAD_FUNCTION(VertexArrayRangeAPPLE);
    GLFL_LOAD_FUNCTION(FlushVertexArrayRangeAPPLE);
    GLFL_LOAD_FUNCTION(VertexArrayParameteriAPPLE);
}
void glfl::load_extension_GL_APPLE_vertex_program_evaluators()
{
    GLFL_LOAD_FUNCTION(EnableVertexAttribAPPLE);
    GLFL_LOAD_FUNCTION(DisableVertexAttribAPPLE);
    GLFL_LOAD_FUNCTION(IsVertexAttribEnabledAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib1dAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib1fAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib2dAPPLE);
    GLFL_LOAD_FUNCTION(MapVertexAttrib2fAPPLE);
}
void glfl::load_extension_GL_APPLE_ycbcr_422() {}
void glfl::load_extension_GL_ARB_ES2_compatibility()
{
    GLFL_LOAD_FUNCTION(ReleaseShaderCompiler);
    GLFL_LOAD_FUNCTION(ShaderBinary);
    GLFL_LOAD_FUNCTION(GetShaderPrecisionFormat);
    GLFL_LOAD_FUNCTION(DepthRangef);
    GLFL_LOAD_FUNCTION(ClearDepthf);
}
void glfl::load_extension_GL_ARB_ES3_1_compatibility()
{
    GLFL_LOAD_FUNCTION(MemoryBarrierByRegion);
}
void glfl::load_extension_GL_ARB_ES3_2_compatibility()
{
    GLFL_LOAD_FUNCTION(PrimitiveBoundingBoxARB);
}
void glfl::load_extension_GL_ARB_ES3_compatibility() {}
void glfl::load_extension_GL_ARB_arrays_of_arrays() {}
void glfl::load_extension_GL_ARB_base_instance()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedBaseInstance);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseInstance);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexBaseInstance);
}
void glfl::load_extension_GL_ARB_bindless_texture()
{
    GLFL_LOAD_FUNCTION(GetTextureHandleARB);
    GLFL_LOAD_FUNCTION(GetTextureSamplerHandleARB);
    GLFL_LOAD_FUNCTION(MakeTextureHandleResidentARB);
    GLFL_LOAD_FUNCTION(MakeTextureHandleNonResidentARB);
    GLFL_LOAD_FUNCTION(GetImageHandleARB);
    GLFL_LOAD_FUNCTION(MakeImageHandleResidentARB);
    GLFL_LOAD_FUNCTION(MakeImageHandleNonResidentARB);
    GLFL_LOAD_FUNCTION(UniformHandleui64ARB);
    GLFL_LOAD_FUNCTION(UniformHandleui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64vARB);
    GLFL_LOAD_FUNCTION(IsTextureHandleResidentARB);
    GLFL_LOAD_FUNCTION(IsImageHandleResidentARB);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64ARB);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64vARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribLui64vARB);
}
void glfl::load_extension_GL_ARB_blend_func_extended()
{
    GLFL_LOAD_FUNCTION(BindFragDataLocationIndexed);
    GLFL_LOAD_FUNCTION(GetFragDataIndex);
}
void glfl::load_extension_GL_ARB_buffer_storage()
{
    GLFL_LOAD_FUNCTION(BufferStorage);
}
void glfl::load_extension_GL_ARB_cl_event()
{
    GLFL_LOAD_FUNCTION(CreateSyncFromCLeventARB);
}
void glfl::load_extension_GL_ARB_clear_buffer_object()
{
    GLFL_LOAD_FUNCTION(ClearBufferData);
    GLFL_LOAD_FUNCTION(ClearBufferSubData);
}
void glfl::load_extension_GL_ARB_clear_texture()
{
    GLFL_LOAD_FUNCTION(ClearTexImage);
    GLFL_LOAD_FUNCTION(ClearTexSubImage);
}
void glfl::load_extension_GL_ARB_clip_control()
{
    GLFL_LOAD_FUNCTION(ClipControl);
}
void glfl::load_extension_GL_ARB_color_buffer_float()
{
    GLFL_LOAD_FUNCTION(ClampColorARB);
}
void glfl::load_extension_GL_ARB_compatibility() {}
void glfl::load_extension_GL_ARB_compressed_texture_pixel_storage() {}
void glfl::load_extension_GL_ARB_compute_shader()
{
    GLFL_LOAD_FUNCTION(DispatchCompute);
    GLFL_LOAD_FUNCTION(DispatchComputeIndirect);
}
void glfl::load_extension_GL_ARB_compute_variable_group_size()
{
    GLFL_LOAD_FUNCTION(DispatchComputeGroupSizeARB);
}
void glfl::load_extension_GL_ARB_conditional_render_inverted() {}
void glfl::load_extension_GL_ARB_conservative_depth() {}
void glfl::load_extension_GL_ARB_copy_buffer()
{
    GLFL_LOAD_FUNCTION(CopyBufferSubData);
}
void glfl::load_extension_GL_ARB_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubData);
}
void glfl::load_extension_GL_ARB_cull_distance() {}
void glfl::load_extension_GL_ARB_debug_output()
{
    GLFL_LOAD_FUNCTION(DebugMessageControlARB);
    GLFL_LOAD_FUNCTION(DebugMessageInsertARB);
    GLFL_LOAD_FUNCTION(DebugMessageCallbackARB);
    GLFL_LOAD_FUNCTION(GetDebugMessageLogARB);
}
void glfl::load_extension_GL_ARB_depth_buffer_float() {}
void glfl::load_extension_GL_ARB_depth_clamp() {}
void glfl::load_extension_GL_ARB_depth_texture() {}
void glfl::load_extension_GL_ARB_derivative_control() {}
void glfl::load_extension_GL_ARB_direct_state_access()
{
    GLFL_LOAD_FUNCTION(CreateTransformFeedbacks);
    GLFL_LOAD_FUNCTION(TransformFeedbackBufferBase);
    GLFL_LOAD_FUNCTION(TransformFeedbackBufferRange);
    GLFL_LOAD_FUNCTION(GetTransformFeedbackiv);
    GLFL_LOAD_FUNCTION(GetTransformFeedbacki_v);
    GLFL_LOAD_FUNCTION(GetTransformFeedbacki64_v);
    GLFL_LOAD_FUNCTION(CreateBuffers);
    GLFL_LOAD_FUNCTION(NamedBufferStorage);
    GLFL_LOAD_FUNCTION(NamedBufferData);
    GLFL_LOAD_FUNCTION(NamedBufferSubData);
    GLFL_LOAD_FUNCTION(CopyNamedBufferSubData);
    GLFL_LOAD_FUNCTION(ClearNamedBufferData);
    GLFL_LOAD_FUNCTION(ClearNamedBufferSubData);
    GLFL_LOAD_FUNCTION(MapNamedBuffer);
    GLFL_LOAD_FUNCTION(MapNamedBufferRange);
    GLFL_LOAD_FUNCTION(UnmapNamedBuffer);
    GLFL_LOAD_FUNCTION(FlushMappedNamedBufferRange);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameteriv);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameteri64v);
    GLFL_LOAD_FUNCTION(GetNamedBufferPointerv);
    GLFL_LOAD_FUNCTION(GetNamedBufferSubData);
    GLFL_LOAD_FUNCTION(CreateFramebuffers);
    GLFL_LOAD_FUNCTION(NamedFramebufferRenderbuffer);
    GLFL_LOAD_FUNCTION(NamedFramebufferParameteri);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureLayer);
    GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffer);
    GLFL_LOAD_FUNCTION(NamedFramebufferDrawBuffers);
    GLFL_LOAD_FUNCTION(NamedFramebufferReadBuffer);
    GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferData);
    GLFL_LOAD_FUNCTION(InvalidateNamedFramebufferSubData);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferiv);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferuiv);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferfv);
    GLFL_LOAD_FUNCTION(ClearNamedFramebufferfi);
    GLFL_LOAD_FUNCTION(BlitNamedFramebuffer);
    GLFL_LOAD_FUNCTION(CheckNamedFramebufferStatus);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferParameteriv);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferAttachmentParameteriv);
    GLFL_LOAD_FUNCTION(CreateRenderbuffers);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorage);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisample);
    GLFL_LOAD_FUNCTION(GetNamedRenderbufferParameteriv);
    GLFL_LOAD_FUNCTION(CreateTextures);
    GLFL_LOAD_FUNCTION(TextureBuffer);
    GLFL_LOAD_FUNCTION(TextureBufferRange);
    GLFL_LOAD_FUNCTION(TextureStorage1D);
    GLFL_LOAD_FUNCTION(TextureStorage2D);
    GLFL_LOAD_FUNCTION(TextureStorage3D);
    GLFL_LOAD_FUNCTION(TextureStorage2DMultisample);
    GLFL_LOAD_FUNCTION(TextureStorage3DMultisample);
    GLFL_LOAD_FUNCTION(TextureSubImage1D);
    GLFL_LOAD_FUNCTION(TextureSubImage2D);
    GLFL_LOAD_FUNCTION(TextureSubImage3D);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage1D);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage2D);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage3D);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage1D);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage2D);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage3D);
    GLFL_LOAD_FUNCTION(TextureParameterf);
    GLFL_LOAD_FUNCTION(TextureParameterfv);
    GLFL_LOAD_FUNCTION(TextureParameteri);
    GLFL_LOAD_FUNCTION(TextureParameterIiv);
    GLFL_LOAD_FUNCTION(TextureParameterIuiv);
    GLFL_LOAD_FUNCTION(TextureParameteriv);
    GLFL_LOAD_FUNCTION(GenerateTextureMipmap);
    GLFL_LOAD_FUNCTION(BindTextureUnit);
    GLFL_LOAD_FUNCTION(GetTextureImage);
    GLFL_LOAD_FUNCTION(GetCompressedTextureImage);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameterfv);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameteriv);
    GLFL_LOAD_FUNCTION(GetTextureParameterfv);
    GLFL_LOAD_FUNCTION(GetTextureParameterIiv);
    GLFL_LOAD_FUNCTION(GetTextureParameterIuiv);
    GLFL_LOAD_FUNCTION(GetTextureParameteriv);
    GLFL_LOAD_FUNCTION(CreateVertexArrays);
    GLFL_LOAD_FUNCTION(DisableVertexArrayAttrib);
    GLFL_LOAD_FUNCTION(EnableVertexArrayAttrib);
    GLFL_LOAD_FUNCTION(VertexArrayElementBuffer);
    GLFL_LOAD_FUNCTION(VertexArrayVertexBuffer);
    GLFL_LOAD_FUNCTION(VertexArrayVertexBuffers);
    GLFL_LOAD_FUNCTION(VertexArrayAttribBinding);
    GLFL_LOAD_FUNCTION(VertexArrayAttribFormat);
    GLFL_LOAD_FUNCTION(VertexArrayAttribIFormat);
    GLFL_LOAD_FUNCTION(VertexArrayAttribLFormat);
    GLFL_LOAD_FUNCTION(VertexArrayBindingDivisor);
    GLFL_LOAD_FUNCTION(GetVertexArrayiv);
    GLFL_LOAD_FUNCTION(GetVertexArrayIndexediv);
    GLFL_LOAD_FUNCTION(GetVertexArrayIndexed64iv);
    GLFL_LOAD_FUNCTION(CreateSamplers);
    GLFL_LOAD_FUNCTION(CreateProgramPipelines);
    GLFL_LOAD_FUNCTION(CreateQueries);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjecti64v);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjectiv);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjectui64v);
    GLFL_LOAD_FUNCTION(GetQueryBufferObjectuiv);
}
void glfl::load_extension_GL_ARB_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersARB);
}
void glfl::load_extension_GL_ARB_draw_buffers_blend()
{
    GLFL_LOAD_FUNCTION(BlendEquationiARB);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateiARB);
    GLFL_LOAD_FUNCTION(BlendFunciARB);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateiARB);
}
void glfl::load_extension_GL_ARB_draw_elements_base_vertex()
{
    GLFL_LOAD_FUNCTION(DrawElementsBaseVertex);
    GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertex);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertex);
    GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertex);
}
void glfl::load_extension_GL_ARB_draw_indirect()
{
    GLFL_LOAD_FUNCTION(DrawArraysIndirect);
    GLFL_LOAD_FUNCTION(DrawElementsIndirect);
}
void glfl::load_extension_GL_ARB_draw_instanced()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedARB);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedARB);
}
void glfl::load_extension_GL_ARB_enhanced_layouts() {}
void glfl::load_extension_GL_ARB_explicit_attrib_location() {}
void glfl::load_extension_GL_ARB_explicit_uniform_location() {}
void glfl::load_extension_GL_ARB_fragment_coord_conventions() {}
void glfl::load_extension_GL_ARB_fragment_layer_viewport() {}
void glfl::load_extension_GL_ARB_fragment_program()
{
    GLFL_LOAD_FUNCTION(ProgramStringARB);
    GLFL_LOAD_FUNCTION(BindProgramARB);
    GLFL_LOAD_FUNCTION(DeleteProgramsARB);
    GLFL_LOAD_FUNCTION(GenProgramsARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramivARB);
    GLFL_LOAD_FUNCTION(GetProgramStringARB);
    GLFL_LOAD_FUNCTION(IsProgramARB);
}
void glfl::load_extension_GL_ARB_fragment_program_shadow() {}
void glfl::load_extension_GL_ARB_fragment_shader() {}
void glfl::load_extension_GL_ARB_fragment_shader_interlock() {}
void glfl::load_extension_GL_ARB_framebuffer_no_attachments()
{
    GLFL_LOAD_FUNCTION(FramebufferParameteri);
    GLFL_LOAD_FUNCTION(GetFramebufferParameteriv);
}
void glfl::load_extension_GL_ARB_framebuffer_object()
{
    GLFL_LOAD_FUNCTION(IsRenderbuffer);
    GLFL_LOAD_FUNCTION(BindRenderbuffer);
    GLFL_LOAD_FUNCTION(DeleteRenderbuffers);
    GLFL_LOAD_FUNCTION(GenRenderbuffers);
    GLFL_LOAD_FUNCTION(RenderbufferStorage);
    GLFL_LOAD_FUNCTION(GetRenderbufferParameteriv);
    GLFL_LOAD_FUNCTION(IsFramebuffer);
    GLFL_LOAD_FUNCTION(BindFramebuffer);
    GLFL_LOAD_FUNCTION(DeleteFramebuffers);
    GLFL_LOAD_FUNCTION(GenFramebuffers);
    GLFL_LOAD_FUNCTION(CheckFramebufferStatus);
    GLFL_LOAD_FUNCTION(FramebufferTexture1D);
    GLFL_LOAD_FUNCTION(FramebufferTexture2D);
    GLFL_LOAD_FUNCTION(FramebufferTexture3D);
    GLFL_LOAD_FUNCTION(FramebufferRenderbuffer);
    GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameteriv);
    GLFL_LOAD_FUNCTION(GenerateMipmap);
    GLFL_LOAD_FUNCTION(BlitFramebuffer);
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisample);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayer);
}
void glfl::load_extension_GL_ARB_framebuffer_sRGB() {}
void glfl::load_extension_GL_ARB_geometry_shader4()
{
    GLFL_LOAD_FUNCTION(ProgramParameteriARB);
    GLFL_LOAD_FUNCTION(FramebufferTextureARB);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerARB);
    GLFL_LOAD_FUNCTION(FramebufferTextureFaceARB);
}
void glfl::load_extension_GL_ARB_get_program_binary()
{
    GLFL_LOAD_FUNCTION(GetProgramBinary);
    GLFL_LOAD_FUNCTION(ProgramBinary);
    GLFL_LOAD_FUNCTION(ProgramParameteri);
}
void glfl::load_extension_GL_ARB_get_texture_sub_image()
{
    GLFL_LOAD_FUNCTION(GetTextureSubImage);
    GLFL_LOAD_FUNCTION(GetCompressedTextureSubImage);
}
void glfl::load_extension_GL_ARB_gpu_shader5() {}
void glfl::load_extension_GL_ARB_gpu_shader_fp64()
{
    GLFL_LOAD_FUNCTION(Uniform1d);
    GLFL_LOAD_FUNCTION(Uniform2d);
    GLFL_LOAD_FUNCTION(Uniform3d);
    GLFL_LOAD_FUNCTION(Uniform4d);
    GLFL_LOAD_FUNCTION(Uniform1dv);
    GLFL_LOAD_FUNCTION(Uniform2dv);
    GLFL_LOAD_FUNCTION(Uniform3dv);
    GLFL_LOAD_FUNCTION(Uniform4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix2dv);
    GLFL_LOAD_FUNCTION(UniformMatrix3dv);
    GLFL_LOAD_FUNCTION(UniformMatrix4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix2x3dv);
    GLFL_LOAD_FUNCTION(UniformMatrix2x4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix3x2dv);
    GLFL_LOAD_FUNCTION(UniformMatrix3x4dv);
    GLFL_LOAD_FUNCTION(UniformMatrix4x2dv);
    GLFL_LOAD_FUNCTION(UniformMatrix4x3dv);
    GLFL_LOAD_FUNCTION(GetUniformdv);
}
void glfl::load_extension_GL_ARB_gpu_shader_int64()
{
    GLFL_LOAD_FUNCTION(Uniform1i64ARB);
    GLFL_LOAD_FUNCTION(Uniform2i64ARB);
    GLFL_LOAD_FUNCTION(Uniform3i64ARB);
    GLFL_LOAD_FUNCTION(Uniform4i64ARB);
    GLFL_LOAD_FUNCTION(Uniform1i64vARB);
    GLFL_LOAD_FUNCTION(Uniform2i64vARB);
    GLFL_LOAD_FUNCTION(Uniform3i64vARB);
    GLFL_LOAD_FUNCTION(Uniform4i64vARB);
    GLFL_LOAD_FUNCTION(Uniform1ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform2ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform3ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform4ui64ARB);
    GLFL_LOAD_FUNCTION(Uniform1ui64vARB);
    GLFL_LOAD_FUNCTION(Uniform2ui64vARB);
    GLFL_LOAD_FUNCTION(Uniform3ui64vARB);
    GLFL_LOAD_FUNCTION(Uniform4ui64vARB);
    GLFL_LOAD_FUNCTION(GetUniformi64vARB);
    GLFL_LOAD_FUNCTION(GetUniformui64vARB);
    GLFL_LOAD_FUNCTION(GetnUniformi64vARB);
    GLFL_LOAD_FUNCTION(GetnUniformui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64ARB);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64vARB);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64vARB);
}
void glfl::load_extension_GL_ARB_half_float_pixel() {}
void glfl::load_extension_GL_ARB_half_float_vertex() {}
void glfl::load_extension_GL_ARB_imaging()
{
    GLFL_LOAD_FUNCTION(BlendColor);
    GLFL_LOAD_FUNCTION(BlendEquation);
    GLFL_LOAD_FUNCTION(ColorTable);
    GLFL_LOAD_FUNCTION(ColorTableParameterfv);
    GLFL_LOAD_FUNCTION(ColorTableParameteriv);
    GLFL_LOAD_FUNCTION(CopyColorTable);
    GLFL_LOAD_FUNCTION(GetColorTable);
    GLFL_LOAD_FUNCTION(GetColorTableParameterfv);
    GLFL_LOAD_FUNCTION(GetColorTableParameteriv);
    GLFL_LOAD_FUNCTION(ColorSubTable);
    GLFL_LOAD_FUNCTION(CopyColorSubTable);
    GLFL_LOAD_FUNCTION(ConvolutionFilter1D);
    GLFL_LOAD_FUNCTION(ConvolutionFilter2D);
    GLFL_LOAD_FUNCTION(ConvolutionParameterf);
    GLFL_LOAD_FUNCTION(ConvolutionParameterfv);
    GLFL_LOAD_FUNCTION(ConvolutionParameteri);
    GLFL_LOAD_FUNCTION(ConvolutionParameteriv);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter1D);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter2D);
    GLFL_LOAD_FUNCTION(GetConvolutionFilter);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterfv);
    GLFL_LOAD_FUNCTION(GetConvolutionParameteriv);
    GLFL_LOAD_FUNCTION(GetSeparableFilter);
    GLFL_LOAD_FUNCTION(SeparableFilter2D);
    GLFL_LOAD_FUNCTION(GetHistogram);
    GLFL_LOAD_FUNCTION(GetHistogramParameterfv);
    GLFL_LOAD_FUNCTION(GetHistogramParameteriv);
    GLFL_LOAD_FUNCTION(GetMinmax);
    GLFL_LOAD_FUNCTION(GetMinmaxParameterfv);
    GLFL_LOAD_FUNCTION(GetMinmaxParameteriv);
    GLFL_LOAD_FUNCTION(Histogram);
    GLFL_LOAD_FUNCTION(Minmax);
    GLFL_LOAD_FUNCTION(ResetHistogram);
    GLFL_LOAD_FUNCTION(ResetMinmax);
}
void glfl::load_extension_GL_ARB_indirect_parameters()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectCountARB);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectCountARB);
}
void glfl::load_extension_GL_ARB_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(VertexAttribDivisorARB);
}
void glfl::load_extension_GL_ARB_internalformat_query()
{
    GLFL_LOAD_FUNCTION(GetInternalformativ);
}
void glfl::load_extension_GL_ARB_internalformat_query2()
{
    GLFL_LOAD_FUNCTION(GetInternalformati64v);
}
void glfl::load_extension_GL_ARB_invalidate_subdata()
{
    GLFL_LOAD_FUNCTION(InvalidateTexSubImage);
    GLFL_LOAD_FUNCTION(InvalidateTexImage);
    GLFL_LOAD_FUNCTION(InvalidateBufferSubData);
    GLFL_LOAD_FUNCTION(InvalidateBufferData);
    GLFL_LOAD_FUNCTION(InvalidateFramebuffer);
    GLFL_LOAD_FUNCTION(InvalidateSubFramebuffer);
}
void glfl::load_extension_GL_ARB_map_buffer_alignment() {}
void glfl::load_extension_GL_ARB_map_buffer_range()
{
    GLFL_LOAD_FUNCTION(MapBufferRange);
    GLFL_LOAD_FUNCTION(FlushMappedBufferRange);
}
void glfl::load_extension_GL_ARB_matrix_palette()
{
    GLFL_LOAD_FUNCTION(CurrentPaletteMatrixARB);
    GLFL_LOAD_FUNCTION(MatrixIndexubvARB);
    GLFL_LOAD_FUNCTION(MatrixIndexusvARB);
    GLFL_LOAD_FUNCTION(MatrixIndexuivARB);
    GLFL_LOAD_FUNCTION(MatrixIndexPointerARB);
}
void glfl::load_extension_GL_ARB_multi_bind()
{
    GLFL_LOAD_FUNCTION(BindBuffersBase);
    GLFL_LOAD_FUNCTION(BindBuffersRange);
    GLFL_LOAD_FUNCTION(BindTextures);
    GLFL_LOAD_FUNCTION(BindSamplers);
    GLFL_LOAD_FUNCTION(BindImageTextures);
    GLFL_LOAD_FUNCTION(BindVertexBuffers);
}
void glfl::load_extension_GL_ARB_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirect);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirect);
}
void glfl::load_extension_GL_ARB_multisample()
{
    GLFL_LOAD_FUNCTION(SampleCoverageARB);
}
void glfl::load_extension_GL_ARB_multitexture()
{
    GLFL_LOAD_FUNCTION(ActiveTextureARB);
    GLFL_LOAD_FUNCTION(ClientActiveTextureARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord1svARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord2svARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord3svARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4dARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4dvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4fARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4fvARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4iARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4ivARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4sARB);
    GLFL_LOAD_FUNCTION(MultiTexCoord4svARB);
}
void glfl::load_extension_GL_ARB_occlusion_query()
{
    GLFL_LOAD_FUNCTION(GenQueriesARB);
    GLFL_LOAD_FUNCTION(DeleteQueriesARB);
    GLFL_LOAD_FUNCTION(IsQueryARB);
    GLFL_LOAD_FUNCTION(BeginQueryARB);
    GLFL_LOAD_FUNCTION(EndQueryARB);
    GLFL_LOAD_FUNCTION(GetQueryivARB);
    GLFL_LOAD_FUNCTION(GetQueryObjectivARB);
    GLFL_LOAD_FUNCTION(GetQueryObjectuivARB);
}
void glfl::load_extension_GL_ARB_occlusion_query2() {}
void glfl::load_extension_GL_ARB_parallel_shader_compile()
{
    GLFL_LOAD_FUNCTION(MaxShaderCompilerThreadsARB);
}
void glfl::load_extension_GL_ARB_pipeline_statistics_query() {}
void glfl::load_extension_GL_ARB_pixel_buffer_object() {}
void glfl::load_extension_GL_ARB_point_parameters()
{
    GLFL_LOAD_FUNCTION(PointParameterfARB);
    GLFL_LOAD_FUNCTION(PointParameterfvARB);
}
void glfl::load_extension_GL_ARB_point_sprite() {}
void glfl::load_extension_GL_ARB_post_depth_coverage() {}
void glfl::load_extension_GL_ARB_program_interface_query()
{
    GLFL_LOAD_FUNCTION(GetProgramInterfaceiv);
    GLFL_LOAD_FUNCTION(GetProgramResourceIndex);
    GLFL_LOAD_FUNCTION(GetProgramResourceName);
    GLFL_LOAD_FUNCTION(GetProgramResourceiv);
    GLFL_LOAD_FUNCTION(GetProgramResourceLocation);
    GLFL_LOAD_FUNCTION(GetProgramResourceLocationIndex);
}
void glfl::load_extension_GL_ARB_provoking_vertex()
{
    GLFL_LOAD_FUNCTION(ProvokingVertex);
}
void glfl::load_extension_GL_ARB_query_buffer_object() {}
void glfl::load_extension_GL_ARB_robust_buffer_access_behavior() {}
void glfl::load_extension_GL_ARB_robustness()
{
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatusARB);
    GLFL_LOAD_FUNCTION(GetnTexImageARB);
    GLFL_LOAD_FUNCTION(ReadnPixelsARB);
    GLFL_LOAD_FUNCTION(GetnCompressedTexImageARB);
    GLFL_LOAD_FUNCTION(GetnUniformfvARB);
    GLFL_LOAD_FUNCTION(GetnUniformivARB);
    GLFL_LOAD_FUNCTION(GetnUniformuivARB);
    GLFL_LOAD_FUNCTION(GetnUniformdvARB);
    GLFL_LOAD_FUNCTION(GetnMapdvARB);
    GLFL_LOAD_FUNCTION(GetnMapfvARB);
    GLFL_LOAD_FUNCTION(GetnMapivARB);
    GLFL_LOAD_FUNCTION(GetnPixelMapfvARB);
    GLFL_LOAD_FUNCTION(GetnPixelMapuivARB);
    GLFL_LOAD_FUNCTION(GetnPixelMapusvARB);
    GLFL_LOAD_FUNCTION(GetnPolygonStippleARB);
    GLFL_LOAD_FUNCTION(GetnColorTableARB);
    GLFL_LOAD_FUNCTION(GetnConvolutionFilterARB);
    GLFL_LOAD_FUNCTION(GetnSeparableFilterARB);
    GLFL_LOAD_FUNCTION(GetnHistogramARB);
    GLFL_LOAD_FUNCTION(GetnMinmaxARB);
}
void glfl::load_extension_GL_ARB_robustness_isolation() {}
void glfl::load_extension_GL_ARB_sample_locations()
{
    GLFL_LOAD_FUNCTION(FramebufferSampleLocationsfvARB);
    GLFL_LOAD_FUNCTION(NamedFramebufferSampleLocationsfvARB);
    GLFL_LOAD_FUNCTION(EvaluateDepthValuesARB);
}
void glfl::load_extension_GL_ARB_sample_shading()
{
    GLFL_LOAD_FUNCTION(MinSampleShadingARB);
}
void glfl::load_extension_GL_ARB_sampler_objects()
{
    GLFL_LOAD_FUNCTION(GenSamplers);
    GLFL_LOAD_FUNCTION(DeleteSamplers);
    GLFL_LOAD_FUNCTION(IsSampler);
    GLFL_LOAD_FUNCTION(BindSampler);
    GLFL_LOAD_FUNCTION(SamplerParameteri);
    GLFL_LOAD_FUNCTION(SamplerParameteriv);
    GLFL_LOAD_FUNCTION(SamplerParameterf);
    GLFL_LOAD_FUNCTION(SamplerParameterfv);
    GLFL_LOAD_FUNCTION(SamplerParameterIiv);
    GLFL_LOAD_FUNCTION(SamplerParameterIuiv);
    GLFL_LOAD_FUNCTION(GetSamplerParameteriv);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIiv);
    GLFL_LOAD_FUNCTION(GetSamplerParameterfv);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIuiv);
}
void glfl::load_extension_GL_ARB_seamless_cube_map() {}
void glfl::load_extension_GL_ARB_seamless_cubemap_per_texture() {}
void glfl::load_extension_GL_ARB_separate_shader_objects()
{
    GLFL_LOAD_FUNCTION(UseProgramStages);
    GLFL_LOAD_FUNCTION(ActiveShaderProgram);
    GLFL_LOAD_FUNCTION(CreateShaderProgramv);
    GLFL_LOAD_FUNCTION(BindProgramPipeline);
    GLFL_LOAD_FUNCTION(DeleteProgramPipelines);
    GLFL_LOAD_FUNCTION(GenProgramPipelines);
    GLFL_LOAD_FUNCTION(IsProgramPipeline);
    GLFL_LOAD_FUNCTION(GetProgramPipelineiv);
    GLFL_LOAD_FUNCTION(ProgramUniform1i);
    GLFL_LOAD_FUNCTION(ProgramUniform1iv);
    GLFL_LOAD_FUNCTION(ProgramUniform1f);
    GLFL_LOAD_FUNCTION(ProgramUniform1fv);
    GLFL_LOAD_FUNCTION(ProgramUniform1d);
    GLFL_LOAD_FUNCTION(ProgramUniform1dv);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui);
    GLFL_LOAD_FUNCTION(ProgramUniform1uiv);
    GLFL_LOAD_FUNCTION(ProgramUniform2i);
    GLFL_LOAD_FUNCTION(ProgramUniform2iv);
    GLFL_LOAD_FUNCTION(ProgramUniform2f);
    GLFL_LOAD_FUNCTION(ProgramUniform2fv);
    GLFL_LOAD_FUNCTION(ProgramUniform2d);
    GLFL_LOAD_FUNCTION(ProgramUniform2dv);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui);
    GLFL_LOAD_FUNCTION(ProgramUniform2uiv);
    GLFL_LOAD_FUNCTION(ProgramUniform3i);
    GLFL_LOAD_FUNCTION(ProgramUniform3iv);
    GLFL_LOAD_FUNCTION(ProgramUniform3f);
    GLFL_LOAD_FUNCTION(ProgramUniform3fv);
    GLFL_LOAD_FUNCTION(ProgramUniform3d);
    GLFL_LOAD_FUNCTION(ProgramUniform3dv);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui);
    GLFL_LOAD_FUNCTION(ProgramUniform3uiv);
    GLFL_LOAD_FUNCTION(ProgramUniform4i);
    GLFL_LOAD_FUNCTION(ProgramUniform4iv);
    GLFL_LOAD_FUNCTION(ProgramUniform4f);
    GLFL_LOAD_FUNCTION(ProgramUniform4fv);
    GLFL_LOAD_FUNCTION(ProgramUniform4d);
    GLFL_LOAD_FUNCTION(ProgramUniform4dv);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui);
    GLFL_LOAD_FUNCTION(ProgramUniform4uiv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4dv);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3dv);
    GLFL_LOAD_FUNCTION(ValidateProgramPipeline);
    GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLog);
}
void glfl::load_extension_GL_ARB_shader_atomic_counter_ops() {}
void glfl::load_extension_GL_ARB_shader_atomic_counters()
{
    GLFL_LOAD_FUNCTION(GetActiveAtomicCounterBufferiv);
}
void glfl::load_extension_GL_ARB_shader_ballot() {}
void glfl::load_extension_GL_ARB_shader_bit_encoding() {}
void glfl::load_extension_GL_ARB_shader_clock() {}
void glfl::load_extension_GL_ARB_shader_draw_parameters() {}
void glfl::load_extension_GL_ARB_shader_group_vote() {}
void glfl::load_extension_GL_ARB_shader_image_load_store()
{
    GLFL_LOAD_FUNCTION(BindImageTexture);
    GLFL_LOAD_FUNCTION(MemoryBarrier);
}
void glfl::load_extension_GL_ARB_shader_image_size() {}
void glfl::load_extension_GL_ARB_shader_objects()
{
    GLFL_LOAD_FUNCTION(DeleteObjectARB);
    GLFL_LOAD_FUNCTION(GetHandleARB);
    GLFL_LOAD_FUNCTION(DetachObjectARB);
    GLFL_LOAD_FUNCTION(CreateShaderObjectARB);
    GLFL_LOAD_FUNCTION(ShaderSourceARB);
    GLFL_LOAD_FUNCTION(CompileShaderARB);
    GLFL_LOAD_FUNCTION(CreateProgramObjectARB);
    GLFL_LOAD_FUNCTION(AttachObjectARB);
    GLFL_LOAD_FUNCTION(LinkProgramARB);
    GLFL_LOAD_FUNCTION(UseProgramObjectARB);
    GLFL_LOAD_FUNCTION(ValidateProgramARB);
    GLFL_LOAD_FUNCTION(Uniform1fARB);
    GLFL_LOAD_FUNCTION(Uniform2fARB);
    GLFL_LOAD_FUNCTION(Uniform3fARB);
    GLFL_LOAD_FUNCTION(Uniform4fARB);
    GLFL_LOAD_FUNCTION(Uniform1iARB);
    GLFL_LOAD_FUNCTION(Uniform2iARB);
    GLFL_LOAD_FUNCTION(Uniform3iARB);
    GLFL_LOAD_FUNCTION(Uniform4iARB);
    GLFL_LOAD_FUNCTION(Uniform1fvARB);
    GLFL_LOAD_FUNCTION(Uniform2fvARB);
    GLFL_LOAD_FUNCTION(Uniform3fvARB);
    GLFL_LOAD_FUNCTION(Uniform4fvARB);
    GLFL_LOAD_FUNCTION(Uniform1ivARB);
    GLFL_LOAD_FUNCTION(Uniform2ivARB);
    GLFL_LOAD_FUNCTION(Uniform3ivARB);
    GLFL_LOAD_FUNCTION(Uniform4ivARB);
    GLFL_LOAD_FUNCTION(UniformMatrix2fvARB);
    GLFL_LOAD_FUNCTION(UniformMatrix3fvARB);
    GLFL_LOAD_FUNCTION(UniformMatrix4fvARB);
    GLFL_LOAD_FUNCTION(GetObjectParameterfvARB);
    GLFL_LOAD_FUNCTION(GetObjectParameterivARB);
    GLFL_LOAD_FUNCTION(GetInfoLogARB);
    GLFL_LOAD_FUNCTION(GetAttachedObjectsARB);
    GLFL_LOAD_FUNCTION(GetUniformLocationARB);
    GLFL_LOAD_FUNCTION(GetActiveUniformARB);
    GLFL_LOAD_FUNCTION(GetUniformfvARB);
    GLFL_LOAD_FUNCTION(GetUniformivARB);
    GLFL_LOAD_FUNCTION(GetShaderSourceARB);
}
void glfl::load_extension_GL_ARB_shader_precision() {}
void glfl::load_extension_GL_ARB_shader_stencil_export() {}
void glfl::load_extension_GL_ARB_shader_storage_buffer_object()
{
    GLFL_LOAD_FUNCTION(ShaderStorageBlockBinding);
}
void glfl::load_extension_GL_ARB_shader_subroutine()
{
    GLFL_LOAD_FUNCTION(GetSubroutineUniformLocation);
    GLFL_LOAD_FUNCTION(GetSubroutineIndex);
    GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformiv);
    GLFL_LOAD_FUNCTION(GetActiveSubroutineUniformName);
    GLFL_LOAD_FUNCTION(GetActiveSubroutineName);
    GLFL_LOAD_FUNCTION(UniformSubroutinesuiv);
    GLFL_LOAD_FUNCTION(GetUniformSubroutineuiv);
    GLFL_LOAD_FUNCTION(GetProgramStageiv);
}
void glfl::load_extension_GL_ARB_shader_texture_image_samples() {}
void glfl::load_extension_GL_ARB_shader_texture_lod() {}
void glfl::load_extension_GL_ARB_shader_viewport_layer_array() {}
void glfl::load_extension_GL_ARB_shading_language_100() {}
void glfl::load_extension_GL_ARB_shading_language_420pack() {}
void glfl::load_extension_GL_ARB_shading_language_include()
{
    GLFL_LOAD_FUNCTION(NamedStringARB);
    GLFL_LOAD_FUNCTION(DeleteNamedStringARB);
    GLFL_LOAD_FUNCTION(CompileShaderIncludeARB);
    GLFL_LOAD_FUNCTION(IsNamedStringARB);
    GLFL_LOAD_FUNCTION(GetNamedStringARB);
    GLFL_LOAD_FUNCTION(GetNamedStringivARB);
}
void glfl::load_extension_GL_ARB_shading_language_packing() {}
void glfl::load_extension_GL_ARB_shadow() {}
void glfl::load_extension_GL_ARB_shadow_ambient() {}
void glfl::load_extension_GL_ARB_sparse_buffer()
{
    GLFL_LOAD_FUNCTION(BufferPageCommitmentARB);
    GLFL_LOAD_FUNCTION(NamedBufferPageCommitmentEXT);
    GLFL_LOAD_FUNCTION(NamedBufferPageCommitmentARB);
}
void glfl::load_extension_GL_ARB_sparse_texture()
{
    GLFL_LOAD_FUNCTION(TexPageCommitmentARB);
}
void glfl::load_extension_GL_ARB_sparse_texture2() {}
void glfl::load_extension_GL_ARB_sparse_texture_clamp() {}
void glfl::load_extension_GL_ARB_stencil_texturing() {}
void glfl::load_extension_GL_ARB_sync()
{
    GLFL_LOAD_FUNCTION(FenceSync);
    GLFL_LOAD_FUNCTION(IsSync);
    GLFL_LOAD_FUNCTION(DeleteSync);
    GLFL_LOAD_FUNCTION(ClientWaitSync);
    GLFL_LOAD_FUNCTION(WaitSync);
    GLFL_LOAD_FUNCTION(GetInteger64v);
    GLFL_LOAD_FUNCTION(GetSynciv);
}
void glfl::load_extension_GL_ARB_tessellation_shader()
{
    GLFL_LOAD_FUNCTION(PatchParameteri);
    GLFL_LOAD_FUNCTION(PatchParameterfv);
}
void glfl::load_extension_GL_ARB_texture_barrier()
{
    GLFL_LOAD_FUNCTION(TextureBarrier);
}
void glfl::load_extension_GL_ARB_texture_border_clamp() {}
void glfl::load_extension_GL_ARB_texture_buffer_object()
{
    GLFL_LOAD_FUNCTION(TexBufferARB);
}
void glfl::load_extension_GL_ARB_texture_buffer_object_rgb32() {}
void glfl::load_extension_GL_ARB_texture_buffer_range()
{
    GLFL_LOAD_FUNCTION(TexBufferRange);
}
void glfl::load_extension_GL_ARB_texture_compression()
{
    GLFL_LOAD_FUNCTION(CompressedTexImage3DARB);
    GLFL_LOAD_FUNCTION(CompressedTexImage2DARB);
    GLFL_LOAD_FUNCTION(CompressedTexImage1DARB);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage3DARB);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage2DARB);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage1DARB);
    GLFL_LOAD_FUNCTION(GetCompressedTexImageARB);
}
void glfl::load_extension_GL_ARB_texture_compression_bptc() {}
void glfl::load_extension_GL_ARB_texture_compression_rgtc() {}
void glfl::load_extension_GL_ARB_texture_cube_map() {}
void glfl::load_extension_GL_ARB_texture_cube_map_array() {}
void glfl::load_extension_GL_ARB_texture_env_add() {}
void glfl::load_extension_GL_ARB_texture_env_combine() {}
void glfl::load_extension_GL_ARB_texture_env_crossbar() {}
void glfl::load_extension_GL_ARB_texture_env_dot3() {}
void glfl::load_extension_GL_ARB_texture_filter_minmax() {}
void glfl::load_extension_GL_ARB_texture_float() {}
void glfl::load_extension_GL_ARB_texture_gather() {}
void glfl::load_extension_GL_ARB_texture_mirror_clamp_to_edge() {}
void glfl::load_extension_GL_ARB_texture_mirrored_repeat() {}
void glfl::load_extension_GL_ARB_texture_multisample()
{
    GLFL_LOAD_FUNCTION(TexImage2DMultisample);
    GLFL_LOAD_FUNCTION(TexImage3DMultisample);
    GLFL_LOAD_FUNCTION(GetMultisamplefv);
    GLFL_LOAD_FUNCTION(SampleMaski);
}
void glfl::load_extension_GL_ARB_texture_non_power_of_two() {}
void glfl::load_extension_GL_ARB_texture_query_levels() {}
void glfl::load_extension_GL_ARB_texture_query_lod() {}
void glfl::load_extension_GL_ARB_texture_rectangle() {}
void glfl::load_extension_GL_ARB_texture_rg() {}
void glfl::load_extension_GL_ARB_texture_rgb10_a2ui() {}
void glfl::load_extension_GL_ARB_texture_stencil8() {}
void glfl::load_extension_GL_ARB_texture_storage()
{
    GLFL_LOAD_FUNCTION(TexStorage1D);
    GLFL_LOAD_FUNCTION(TexStorage2D);
    GLFL_LOAD_FUNCTION(TexStorage3D);
}
void glfl::load_extension_GL_ARB_texture_storage_multisample()
{
    GLFL_LOAD_FUNCTION(TexStorage2DMultisample);
    GLFL_LOAD_FUNCTION(TexStorage3DMultisample);
}
void glfl::load_extension_GL_ARB_texture_swizzle() {}
void glfl::load_extension_GL_ARB_texture_view()
{
    GLFL_LOAD_FUNCTION(TextureView);
}
void glfl::load_extension_GL_ARB_timer_query()
{
    GLFL_LOAD_FUNCTION(QueryCounter);
    GLFL_LOAD_FUNCTION(GetQueryObjecti64v);
    GLFL_LOAD_FUNCTION(GetQueryObjectui64v);
}
void glfl::load_extension_GL_ARB_transform_feedback2()
{
    GLFL_LOAD_FUNCTION(BindTransformFeedback);
    GLFL_LOAD_FUNCTION(DeleteTransformFeedbacks);
    GLFL_LOAD_FUNCTION(GenTransformFeedbacks);
    GLFL_LOAD_FUNCTION(IsTransformFeedback);
    GLFL_LOAD_FUNCTION(PauseTransformFeedback);
    GLFL_LOAD_FUNCTION(ResumeTransformFeedback);
    GLFL_LOAD_FUNCTION(DrawTransformFeedback);
}
void glfl::load_extension_GL_ARB_transform_feedback3()
{
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackStream);
    GLFL_LOAD_FUNCTION(BeginQueryIndexed);
    GLFL_LOAD_FUNCTION(EndQueryIndexed);
    GLFL_LOAD_FUNCTION(GetQueryIndexediv);
}
void glfl::load_extension_GL_ARB_transform_feedback_instanced()
{
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackInstanced);
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackStreamInstanced);
}
void glfl::load_extension_GL_ARB_transform_feedback_overflow_query() {}
void glfl::load_extension_GL_ARB_transpose_matrix()
{
    GLFL_LOAD_FUNCTION(LoadTransposeMatrixfARB);
    GLFL_LOAD_FUNCTION(LoadTransposeMatrixdARB);
    GLFL_LOAD_FUNCTION(MultTransposeMatrixfARB);
    GLFL_LOAD_FUNCTION(MultTransposeMatrixdARB);
}
void glfl::load_extension_GL_ARB_uniform_buffer_object()
{
    GLFL_LOAD_FUNCTION(GetUniformIndices);
    GLFL_LOAD_FUNCTION(GetActiveUniformsiv);
    GLFL_LOAD_FUNCTION(GetActiveUniformName);
    GLFL_LOAD_FUNCTION(GetUniformBlockIndex);
    GLFL_LOAD_FUNCTION(GetActiveUniformBlockiv);
    GLFL_LOAD_FUNCTION(GetActiveUniformBlockName);
    GLFL_LOAD_FUNCTION(UniformBlockBinding);
    GLFL_LOAD_FUNCTION(BindBufferRange);
    GLFL_LOAD_FUNCTION(BindBufferBase);
    GLFL_LOAD_FUNCTION(GetIntegeri_v);
}
void glfl::load_extension_GL_ARB_vertex_array_bgra() {}
void glfl::load_extension_GL_ARB_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(BindVertexArray);
    GLFL_LOAD_FUNCTION(DeleteVertexArrays);
    GLFL_LOAD_FUNCTION(GenVertexArrays);
    GLFL_LOAD_FUNCTION(IsVertexArray);
}
void glfl::load_extension_GL_ARB_vertex_attrib_64bit()
{
    GLFL_LOAD_FUNCTION(VertexAttribL1d);
    GLFL_LOAD_FUNCTION(VertexAttribL2d);
    GLFL_LOAD_FUNCTION(VertexAttribL3d);
    GLFL_LOAD_FUNCTION(VertexAttribL4d);
    GLFL_LOAD_FUNCTION(VertexAttribL1dv);
    GLFL_LOAD_FUNCTION(VertexAttribL2dv);
    GLFL_LOAD_FUNCTION(VertexAttribL3dv);
    GLFL_LOAD_FUNCTION(VertexAttribL4dv);
    GLFL_LOAD_FUNCTION(VertexAttribLPointer);
    GLFL_LOAD_FUNCTION(GetVertexAttribLdv);
}
void glfl::load_extension_GL_ARB_vertex_attrib_binding()
{
    GLFL_LOAD_FUNCTION(BindVertexBuffer);
    GLFL_LOAD_FUNCTION(VertexAttribFormat);
    GLFL_LOAD_FUNCTION(VertexAttribIFormat);
    GLFL_LOAD_FUNCTION(VertexAttribLFormat);
    GLFL_LOAD_FUNCTION(VertexAttribBinding);
    GLFL_LOAD_FUNCTION(VertexBindingDivisor);
}
void glfl::load_extension_GL_ARB_vertex_blend()
{
    GLFL_LOAD_FUNCTION(WeightbvARB);
    GLFL_LOAD_FUNCTION(WeightsvARB);
    GLFL_LOAD_FUNCTION(WeightivARB);
    GLFL_LOAD_FUNCTION(WeightfvARB);
    GLFL_LOAD_FUNCTION(WeightdvARB);
    GLFL_LOAD_FUNCTION(WeightubvARB);
    GLFL_LOAD_FUNCTION(WeightusvARB);
    GLFL_LOAD_FUNCTION(WeightuivARB);
    GLFL_LOAD_FUNCTION(WeightPointerARB);
    GLFL_LOAD_FUNCTION(VertexBlendARB);
}
void glfl::load_extension_GL_ARB_vertex_buffer_object()
{
    GLFL_LOAD_FUNCTION(BindBufferARB);
    GLFL_LOAD_FUNCTION(DeleteBuffersARB);
    GLFL_LOAD_FUNCTION(GenBuffersARB);
    GLFL_LOAD_FUNCTION(IsBufferARB);
    GLFL_LOAD_FUNCTION(BufferDataARB);
    GLFL_LOAD_FUNCTION(BufferSubDataARB);
    GLFL_LOAD_FUNCTION(GetBufferSubDataARB);
    GLFL_LOAD_FUNCTION(MapBufferARB);
    GLFL_LOAD_FUNCTION(UnmapBufferARB);
    GLFL_LOAD_FUNCTION(GetBufferParameterivARB);
    GLFL_LOAD_FUNCTION(GetBufferPointervARB);
}
void glfl::load_extension_GL_ARB_vertex_program()
{
    GLFL_LOAD_FUNCTION(VertexAttrib1dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NbvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NsvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NuivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NusvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4bvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4uivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4usvARB);
    GLFL_LOAD_FUNCTION(VertexAttribPointerARB);
    GLFL_LOAD_FUNCTION(EnableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(DisableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(ProgramStringARB);
    GLFL_LOAD_FUNCTION(BindProgramARB);
    GLFL_LOAD_FUNCTION(DeleteProgramsARB);
    GLFL_LOAD_FUNCTION(GenProgramsARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramEnvParameter4fvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4dvARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fARB);
    GLFL_LOAD_FUNCTION(ProgramLocalParameter4fvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterdvARB);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterfvARB);
    GLFL_LOAD_FUNCTION(GetProgramivARB);
    GLFL_LOAD_FUNCTION(GetProgramStringARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribdvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribfvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribivARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribPointervARB);
    GLFL_LOAD_FUNCTION(IsProgramARB);
}
void glfl::load_extension_GL_ARB_vertex_shader()
{
    GLFL_LOAD_FUNCTION(VertexAttrib1fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4sARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib1dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib2dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib3dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4fvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4svARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4dvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4bvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4usvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4uivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NbvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NsvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NivARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NubvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NusvARB);
    GLFL_LOAD_FUNCTION(VertexAttrib4NuivARB);
    GLFL_LOAD_FUNCTION(VertexAttribPointerARB);
    GLFL_LOAD_FUNCTION(EnableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(DisableVertexAttribArrayARB);
    GLFL_LOAD_FUNCTION(BindAttribLocationARB);
    GLFL_LOAD_FUNCTION(GetActiveAttribARB);
    GLFL_LOAD_FUNCTION(GetAttribLocationARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribdvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribfvARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribivARB);
    GLFL_LOAD_FUNCTION(GetVertexAttribPointervARB);
}
void glfl::load_extension_GL_ARB_vertex_type_10f_11f_11f_rev() {}
void glfl::load_extension_GL_ARB_vertex_type_2_10_10_10_rev()
{
    GLFL_LOAD_FUNCTION(VertexAttribP1ui);
    GLFL_LOAD_FUNCTION(VertexAttribP1uiv);
    GLFL_LOAD_FUNCTION(VertexAttribP2ui);
    GLFL_LOAD_FUNCTION(VertexAttribP2uiv);
    GLFL_LOAD_FUNCTION(VertexAttribP3ui);
    GLFL_LOAD_FUNCTION(VertexAttribP3uiv);
    GLFL_LOAD_FUNCTION(VertexAttribP4ui);
    GLFL_LOAD_FUNCTION(VertexAttribP4uiv);
    GLFL_LOAD_FUNCTION(VertexP2ui);
    GLFL_LOAD_FUNCTION(VertexP2uiv);
    GLFL_LOAD_FUNCTION(VertexP3ui);
    GLFL_LOAD_FUNCTION(VertexP3uiv);
    GLFL_LOAD_FUNCTION(VertexP4ui);
    GLFL_LOAD_FUNCTION(VertexP4uiv);
    GLFL_LOAD_FUNCTION(TexCoordP1ui);
    GLFL_LOAD_FUNCTION(TexCoordP1uiv);
    GLFL_LOAD_FUNCTION(TexCoordP2ui);
    GLFL_LOAD_FUNCTION(TexCoordP2uiv);
    GLFL_LOAD_FUNCTION(TexCoordP3ui);
    GLFL_LOAD_FUNCTION(TexCoordP3uiv);
    GLFL_LOAD_FUNCTION(TexCoordP4ui);
    GLFL_LOAD_FUNCTION(TexCoordP4uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP1ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP1uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP2ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP2uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP3ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP3uiv);
    GLFL_LOAD_FUNCTION(MultiTexCoordP4ui);
    GLFL_LOAD_FUNCTION(MultiTexCoordP4uiv);
    GLFL_LOAD_FUNCTION(NormalP3ui);
    GLFL_LOAD_FUNCTION(NormalP3uiv);
    GLFL_LOAD_FUNCTION(ColorP3ui);
    GLFL_LOAD_FUNCTION(ColorP3uiv);
    GLFL_LOAD_FUNCTION(ColorP4ui);
    GLFL_LOAD_FUNCTION(ColorP4uiv);
    GLFL_LOAD_FUNCTION(SecondaryColorP3ui);
    GLFL_LOAD_FUNCTION(SecondaryColorP3uiv);
}
void glfl::load_extension_GL_ARB_viewport_array()
{
    GLFL_LOAD_FUNCTION(ViewportArrayv);
    GLFL_LOAD_FUNCTION(ViewportIndexedf);
    GLFL_LOAD_FUNCTION(ViewportIndexedfv);
    GLFL_LOAD_FUNCTION(ScissorArrayv);
    GLFL_LOAD_FUNCTION(ScissorIndexed);
    GLFL_LOAD_FUNCTION(ScissorIndexedv);
    GLFL_LOAD_FUNCTION(DepthRangeArrayv);
    GLFL_LOAD_FUNCTION(DepthRangeIndexed);
    GLFL_LOAD_FUNCTION(GetFloati_v);
    GLFL_LOAD_FUNCTION(GetDoublei_v);
}
void glfl::load_extension_GL_ARB_window_pos()
{
    GLFL_LOAD_FUNCTION(WindowPos2dARB);
    GLFL_LOAD_FUNCTION(WindowPos2dvARB);
    GLFL_LOAD_FUNCTION(WindowPos2fARB);
    GLFL_LOAD_FUNCTION(WindowPos2fvARB);
    GLFL_LOAD_FUNCTION(WindowPos2iARB);
    GLFL_LOAD_FUNCTION(WindowPos2ivARB);
    GLFL_LOAD_FUNCTION(WindowPos2sARB);
    GLFL_LOAD_FUNCTION(WindowPos2svARB);
    GLFL_LOAD_FUNCTION(WindowPos3dARB);
    GLFL_LOAD_FUNCTION(WindowPos3dvARB);
    GLFL_LOAD_FUNCTION(WindowPos3fARB);
    GLFL_LOAD_FUNCTION(WindowPos3fvARB);
    GLFL_LOAD_FUNCTION(WindowPos3iARB);
    GLFL_LOAD_FUNCTION(WindowPos3ivARB);
    GLFL_LOAD_FUNCTION(WindowPos3sARB);
    GLFL_LOAD_FUNCTION(WindowPos3svARB);
}
void glfl::load_extension_GL_ARM_mali_program_binary() {}
void glfl::load_extension_GL_ARM_mali_shader_binary() {}
void glfl::load_extension_GL_ARM_rgba8() {}
void glfl::load_extension_GL_ARM_shader_framebuffer_fetch() {}
void glfl::load_extension_GL_ARM_shader_framebuffer_fetch_depth_stencil() {}
void glfl::load_extension_GL_ATI_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersATI);
}
void glfl::load_extension_GL_ATI_element_array()
{
    GLFL_LOAD_FUNCTION(ElementPointerATI);
    GLFL_LOAD_FUNCTION(DrawElementArrayATI);
    GLFL_LOAD_FUNCTION(DrawRangeElementArrayATI);
}
void glfl::load_extension_GL_ATI_envmap_bumpmap()
{
    GLFL_LOAD_FUNCTION(TexBumpParameterivATI);
    GLFL_LOAD_FUNCTION(TexBumpParameterfvATI);
    GLFL_LOAD_FUNCTION(GetTexBumpParameterivATI);
    GLFL_LOAD_FUNCTION(GetTexBumpParameterfvATI);
}
void glfl::load_extension_GL_ATI_fragment_shader()
{
    GLFL_LOAD_FUNCTION(GenFragmentShadersATI);
    GLFL_LOAD_FUNCTION(BindFragmentShaderATI);
    GLFL_LOAD_FUNCTION(DeleteFragmentShaderATI);
    GLFL_LOAD_FUNCTION(BeginFragmentShaderATI);
    GLFL_LOAD_FUNCTION(EndFragmentShaderATI);
    GLFL_LOAD_FUNCTION(PassTexCoordATI);
    GLFL_LOAD_FUNCTION(SampleMapATI);
    GLFL_LOAD_FUNCTION(ColorFragmentOp1ATI);
    GLFL_LOAD_FUNCTION(ColorFragmentOp2ATI);
    GLFL_LOAD_FUNCTION(ColorFragmentOp3ATI);
    GLFL_LOAD_FUNCTION(AlphaFragmentOp1ATI);
    GLFL_LOAD_FUNCTION(AlphaFragmentOp2ATI);
    GLFL_LOAD_FUNCTION(AlphaFragmentOp3ATI);
    GLFL_LOAD_FUNCTION(SetFragmentShaderConstantATI);
}
void glfl::load_extension_GL_ATI_map_object_buffer()
{
    GLFL_LOAD_FUNCTION(MapObjectBufferATI);
    GLFL_LOAD_FUNCTION(UnmapObjectBufferATI);
}
void glfl::load_extension_GL_ATI_meminfo() {}
void glfl::load_extension_GL_ATI_pixel_format_float() {}
void glfl::load_extension_GL_ATI_pn_triangles()
{
    GLFL_LOAD_FUNCTION(PNTrianglesiATI);
    GLFL_LOAD_FUNCTION(PNTrianglesfATI);
}
void glfl::load_extension_GL_ATI_separate_stencil()
{
    GLFL_LOAD_FUNCTION(StencilOpSeparateATI);
    GLFL_LOAD_FUNCTION(StencilFuncSeparateATI);
}
void glfl::load_extension_GL_ATI_text_fragment_shader() {}
void glfl::load_extension_GL_ATI_texture_env_combine3() {}
void glfl::load_extension_GL_ATI_texture_float() {}
void glfl::load_extension_GL_ATI_texture_mirror_once() {}
void glfl::load_extension_GL_ATI_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(NewObjectBufferATI);
    GLFL_LOAD_FUNCTION(IsObjectBufferATI);
    GLFL_LOAD_FUNCTION(UpdateObjectBufferATI);
    GLFL_LOAD_FUNCTION(GetObjectBufferfvATI);
    GLFL_LOAD_FUNCTION(GetObjectBufferivATI);
    GLFL_LOAD_FUNCTION(FreeObjectBufferATI);
    GLFL_LOAD_FUNCTION(ArrayObjectATI);
    GLFL_LOAD_FUNCTION(GetArrayObjectfvATI);
    GLFL_LOAD_FUNCTION(GetArrayObjectivATI);
    GLFL_LOAD_FUNCTION(VariantArrayObjectATI);
    GLFL_LOAD_FUNCTION(GetVariantArrayObjectfvATI);
    GLFL_LOAD_FUNCTION(GetVariantArrayObjectivATI);
}
void glfl::load_extension_GL_ATI_vertex_attrib_array_object()
{
    GLFL_LOAD_FUNCTION(VertexAttribArrayObjectATI);
    GLFL_LOAD_FUNCTION(GetVertexAttribArrayObjectfvATI);
    GLFL_LOAD_FUNCTION(GetVertexAttribArrayObjectivATI);
}
void glfl::load_extension_GL_ATI_vertex_streams()
{
    GLFL_LOAD_FUNCTION(VertexStream1sATI);
    GLFL_LOAD_FUNCTION(VertexStream1svATI);
    GLFL_LOAD_FUNCTION(VertexStream1iATI);
    GLFL_LOAD_FUNCTION(VertexStream1ivATI);
    GLFL_LOAD_FUNCTION(VertexStream1fATI);
    GLFL_LOAD_FUNCTION(VertexStream1fvATI);
    GLFL_LOAD_FUNCTION(VertexStream1dATI);
    GLFL_LOAD_FUNCTION(VertexStream1dvATI);
    GLFL_LOAD_FUNCTION(VertexStream2sATI);
    GLFL_LOAD_FUNCTION(VertexStream2svATI);
    GLFL_LOAD_FUNCTION(VertexStream2iATI);
    GLFL_LOAD_FUNCTION(VertexStream2ivATI);
    GLFL_LOAD_FUNCTION(VertexStream2fATI);
    GLFL_LOAD_FUNCTION(VertexStream2fvATI);
    GLFL_LOAD_FUNCTION(VertexStream2dATI);
    GLFL_LOAD_FUNCTION(VertexStream2dvATI);
    GLFL_LOAD_FUNCTION(VertexStream3sATI);
    GLFL_LOAD_FUNCTION(VertexStream3svATI);
    GLFL_LOAD_FUNCTION(VertexStream3iATI);
    GLFL_LOAD_FUNCTION(VertexStream3ivATI);
    GLFL_LOAD_FUNCTION(VertexStream3fATI);
    GLFL_LOAD_FUNCTION(VertexStream3fvATI);
    GLFL_LOAD_FUNCTION(VertexStream3dATI);
    GLFL_LOAD_FUNCTION(VertexStream3dvATI);
    GLFL_LOAD_FUNCTION(VertexStream4sATI);
    GLFL_LOAD_FUNCTION(VertexStream4svATI);
    GLFL_LOAD_FUNCTION(VertexStream4iATI);
    GLFL_LOAD_FUNCTION(VertexStream4ivATI);
    GLFL_LOAD_FUNCTION(VertexStream4fATI);
    GLFL_LOAD_FUNCTION(VertexStream4fvATI);
    GLFL_LOAD_FUNCTION(VertexStream4dATI);
    GLFL_LOAD_FUNCTION(VertexStream4dvATI);
    GLFL_LOAD_FUNCTION(NormalStream3bATI);
    GLFL_LOAD_FUNCTION(NormalStream3bvATI);
    GLFL_LOAD_FUNCTION(NormalStream3sATI);
    GLFL_LOAD_FUNCTION(NormalStream3svATI);
    GLFL_LOAD_FUNCTION(NormalStream3iATI);
    GLFL_LOAD_FUNCTION(NormalStream3ivATI);
    GLFL_LOAD_FUNCTION(NormalStream3fATI);
    GLFL_LOAD_FUNCTION(NormalStream3fvATI);
    GLFL_LOAD_FUNCTION(NormalStream3dATI);
    GLFL_LOAD_FUNCTION(NormalStream3dvATI);
    GLFL_LOAD_FUNCTION(ClientActiveVertexStreamATI);
    GLFL_LOAD_FUNCTION(VertexBlendEnviATI);
    GLFL_LOAD_FUNCTION(VertexBlendEnvfATI);
}
void glfl::load_extension_GL_DMP_program_binary() {}
void glfl::load_extension_GL_DMP_shader_binary() {}
void glfl::load_extension_GL_EXT_422_pixels() {}
void glfl::load_extension_GL_EXT_YUV_target() {}
void glfl::load_extension_GL_EXT_abgr() {}
void glfl::load_extension_GL_EXT_base_instance()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedBaseInstanceEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseInstanceEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexBaseInstanceEXT);
}
void glfl::load_extension_GL_EXT_bgra() {}
void glfl::load_extension_GL_EXT_bindable_uniform()
{
    GLFL_LOAD_FUNCTION(UniformBufferEXT);
    GLFL_LOAD_FUNCTION(GetUniformBufferSizeEXT);
    GLFL_LOAD_FUNCTION(GetUniformOffsetEXT);
}
void glfl::load_extension_GL_EXT_blend_color()
{
    GLFL_LOAD_FUNCTION(BlendColorEXT);
}
void glfl::load_extension_GL_EXT_blend_equation_separate()
{
    GLFL_LOAD_FUNCTION(BlendEquationSeparateEXT);
}
void glfl::load_extension_GL_EXT_blend_func_extended()
{
    GLFL_LOAD_FUNCTION(BindFragDataLocationIndexedEXT);
    GLFL_LOAD_FUNCTION(BindFragDataLocationEXT);
    GLFL_LOAD_FUNCTION(GetProgramResourceLocationIndexEXT);
    GLFL_LOAD_FUNCTION(GetFragDataIndexEXT);
}
void glfl::load_extension_GL_EXT_blend_func_separate()
{
    GLFL_LOAD_FUNCTION(BlendFuncSeparateEXT);
}
void glfl::load_extension_GL_EXT_blend_logic_op() {}
void glfl::load_extension_GL_EXT_blend_minmax()
{
    GLFL_LOAD_FUNCTION(BlendEquationEXT);
}
void glfl::load_extension_GL_EXT_blend_subtract() {}
void glfl::load_extension_GL_EXT_buffer_storage()
{
    GLFL_LOAD_FUNCTION(BufferStorageEXT);
}
void glfl::load_extension_GL_EXT_clear_texture()
{
    GLFL_LOAD_FUNCTION(ClearTexImageEXT);
    GLFL_LOAD_FUNCTION(ClearTexSubImageEXT);
}
void glfl::load_extension_GL_EXT_clip_cull_distance() {}
void glfl::load_extension_GL_EXT_clip_volume_hint() {}
void glfl::load_extension_GL_EXT_cmyka() {}
void glfl::load_extension_GL_EXT_color_buffer_float() {}
void glfl::load_extension_GL_EXT_color_buffer_half_float() {}
void glfl::load_extension_GL_EXT_color_subtable()
{
    GLFL_LOAD_FUNCTION(ColorSubTableEXT);
    GLFL_LOAD_FUNCTION(CopyColorSubTableEXT);
}
void glfl::load_extension_GL_EXT_compiled_vertex_array()
{
    GLFL_LOAD_FUNCTION(LockArraysEXT);
    GLFL_LOAD_FUNCTION(UnlockArraysEXT);
}
void glfl::load_extension_GL_EXT_conservative_depth() {}
void glfl::load_extension_GL_EXT_convolution()
{
    GLFL_LOAD_FUNCTION(ConvolutionFilter1DEXT);
    GLFL_LOAD_FUNCTION(ConvolutionFilter2DEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameterfEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameterfvEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameteriEXT);
    GLFL_LOAD_FUNCTION(ConvolutionParameterivEXT);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter1DEXT);
    GLFL_LOAD_FUNCTION(CopyConvolutionFilter2DEXT);
    GLFL_LOAD_FUNCTION(GetConvolutionFilterEXT);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterivEXT);
    GLFL_LOAD_FUNCTION(GetSeparableFilterEXT);
    GLFL_LOAD_FUNCTION(SeparableFilter2DEXT);
}
void glfl::load_extension_GL_EXT_coordinate_frame()
{
    GLFL_LOAD_FUNCTION(Tangent3bEXT);
    GLFL_LOAD_FUNCTION(Tangent3bvEXT);
    GLFL_LOAD_FUNCTION(Tangent3dEXT);
    GLFL_LOAD_FUNCTION(Tangent3dvEXT);
    GLFL_LOAD_FUNCTION(Tangent3fEXT);
    GLFL_LOAD_FUNCTION(Tangent3fvEXT);
    GLFL_LOAD_FUNCTION(Tangent3iEXT);
    GLFL_LOAD_FUNCTION(Tangent3ivEXT);
    GLFL_LOAD_FUNCTION(Tangent3sEXT);
    GLFL_LOAD_FUNCTION(Tangent3svEXT);
    GLFL_LOAD_FUNCTION(Binormal3bEXT);
    GLFL_LOAD_FUNCTION(Binormal3bvEXT);
    GLFL_LOAD_FUNCTION(Binormal3dEXT);
    GLFL_LOAD_FUNCTION(Binormal3dvEXT);
    GLFL_LOAD_FUNCTION(Binormal3fEXT);
    GLFL_LOAD_FUNCTION(Binormal3fvEXT);
    GLFL_LOAD_FUNCTION(Binormal3iEXT);
    GLFL_LOAD_FUNCTION(Binormal3ivEXT);
    GLFL_LOAD_FUNCTION(Binormal3sEXT);
    GLFL_LOAD_FUNCTION(Binormal3svEXT);
    GLFL_LOAD_FUNCTION(TangentPointerEXT);
    GLFL_LOAD_FUNCTION(BinormalPointerEXT);
}
void glfl::load_extension_GL_EXT_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubDataEXT);
}
void glfl::load_extension_GL_EXT_copy_texture()
{
    GLFL_LOAD_FUNCTION(CopyTexImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTexImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTexSubImage3DEXT);
}
void glfl::load_extension_GL_EXT_cull_vertex()
{
    GLFL_LOAD_FUNCTION(CullParameterdvEXT);
    GLFL_LOAD_FUNCTION(CullParameterfvEXT);
}
void glfl::load_extension_GL_EXT_debug_label()
{
    GLFL_LOAD_FUNCTION(LabelObjectEXT);
    GLFL_LOAD_FUNCTION(GetObjectLabelEXT);
}
void glfl::load_extension_GL_EXT_debug_marker()
{
    GLFL_LOAD_FUNCTION(InsertEventMarkerEXT);
    GLFL_LOAD_FUNCTION(PushGroupMarkerEXT);
    GLFL_LOAD_FUNCTION(PopGroupMarkerEXT);
}
void glfl::load_extension_GL_EXT_depth_bounds_test()
{
    GLFL_LOAD_FUNCTION(DepthBoundsEXT);
}
void glfl::load_extension_GL_EXT_direct_state_access()
{
    GLFL_LOAD_FUNCTION(MatrixLoadfEXT);
    GLFL_LOAD_FUNCTION(MatrixLoaddEXT);
    GLFL_LOAD_FUNCTION(MatrixMultfEXT);
    GLFL_LOAD_FUNCTION(MatrixMultdEXT);
    GLFL_LOAD_FUNCTION(MatrixLoadIdentityEXT);
    GLFL_LOAD_FUNCTION(MatrixRotatefEXT);
    GLFL_LOAD_FUNCTION(MatrixRotatedEXT);
    GLFL_LOAD_FUNCTION(MatrixScalefEXT);
    GLFL_LOAD_FUNCTION(MatrixScaledEXT);
    GLFL_LOAD_FUNCTION(MatrixTranslatefEXT);
    GLFL_LOAD_FUNCTION(MatrixTranslatedEXT);
    GLFL_LOAD_FUNCTION(MatrixFrustumEXT);
    GLFL_LOAD_FUNCTION(MatrixOrthoEXT);
    GLFL_LOAD_FUNCTION(MatrixPopEXT);
    GLFL_LOAD_FUNCTION(MatrixPushEXT);
    GLFL_LOAD_FUNCTION(ClientAttribDefaultEXT);
    GLFL_LOAD_FUNCTION(PushClientAttribDefaultEXT);
    GLFL_LOAD_FUNCTION(TextureParameterfEXT);
    GLFL_LOAD_FUNCTION(TextureParameterfvEXT);
    GLFL_LOAD_FUNCTION(TextureParameteriEXT);
    GLFL_LOAD_FUNCTION(TextureParameterivEXT);
    GLFL_LOAD_FUNCTION(TextureImage1DEXT);
    GLFL_LOAD_FUNCTION(TextureImage2DEXT);
    GLFL_LOAD_FUNCTION(TextureSubImage1DEXT);
    GLFL_LOAD_FUNCTION(TextureSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage2DEXT);
    GLFL_LOAD_FUNCTION(GetTextureImageEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterivEXT);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetTextureLevelParameterivEXT);
    GLFL_LOAD_FUNCTION(TextureImage3DEXT);
    GLFL_LOAD_FUNCTION(TextureSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CopyTextureSubImage3DEXT);
    GLFL_LOAD_FUNCTION(BindMultiTextureEXT);
    GLFL_LOAD_FUNCTION(MultiTexCoordPointerEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnvfEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnvfvEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnviEXT);
    GLFL_LOAD_FUNCTION(MultiTexEnvivEXT);
    GLFL_LOAD_FUNCTION(MultiTexGendEXT);
    GLFL_LOAD_FUNCTION(MultiTexGendvEXT);
    GLFL_LOAD_FUNCTION(MultiTexGenfEXT);
    GLFL_LOAD_FUNCTION(MultiTexGenfvEXT);
    GLFL_LOAD_FUNCTION(MultiTexGeniEXT);
    GLFL_LOAD_FUNCTION(MultiTexGenivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexEnvfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexEnvivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexGendvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexGenfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexGenivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameteriEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterfEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterfvEXT);
    GLFL_LOAD_FUNCTION(MultiTexImage1DEXT);
    GLFL_LOAD_FUNCTION(MultiTexImage2DEXT);
    GLFL_LOAD_FUNCTION(MultiTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(MultiTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexImage2DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexImageEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexLevelParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexLevelParameterivEXT);
    GLFL_LOAD_FUNCTION(MultiTexImage3DEXT);
    GLFL_LOAD_FUNCTION(MultiTexSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CopyMultiTexSubImage3DEXT);
    GLFL_LOAD_FUNCTION(EnableClientStateIndexedEXT);
    GLFL_LOAD_FUNCTION(DisableClientStateIndexedEXT);
    GLFL_LOAD_FUNCTION(GetFloatIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetDoubleIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetPointerIndexedvEXT);
    GLFL_LOAD_FUNCTION(EnableIndexedEXT);
    GLFL_LOAD_FUNCTION(DisableIndexedEXT);
    GLFL_LOAD_FUNCTION(IsEnabledIndexedEXT);
    GLFL_LOAD_FUNCTION(GetIntegerIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetBooleanIndexedvEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureImage1DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedTextureSubImage1DEXT);
    GLFL_LOAD_FUNCTION(GetCompressedTextureImageEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexImage1DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexSubImage3DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexSubImage2DEXT);
    GLFL_LOAD_FUNCTION(CompressedMultiTexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(GetCompressedMultiTexImageEXT);
    GLFL_LOAD_FUNCTION(MatrixLoadTransposefEXT);
    GLFL_LOAD_FUNCTION(MatrixLoadTransposedEXT);
    GLFL_LOAD_FUNCTION(MatrixMultTransposefEXT);
    GLFL_LOAD_FUNCTION(MatrixMultTransposedEXT);
    GLFL_LOAD_FUNCTION(NamedBufferDataEXT);
    GLFL_LOAD_FUNCTION(NamedBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(MapNamedBufferEXT);
    GLFL_LOAD_FUNCTION(UnmapNamedBufferEXT);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameterivEXT);
    GLFL_LOAD_FUNCTION(GetNamedBufferPointervEXT);
    GLFL_LOAD_FUNCTION(GetNamedBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fvEXT);
    GLFL_LOAD_FUNCTION(TextureBufferEXT);
    GLFL_LOAD_FUNCTION(MultiTexBufferEXT);
    GLFL_LOAD_FUNCTION(TextureParameterIivEXT);
    GLFL_LOAD_FUNCTION(TextureParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetTextureParameterIuivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(MultiTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetMultiTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameters4fvEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4iEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4ivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParametersI4ivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4uiEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameterI4uivEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParametersI4uivEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterIuivEXT);
    GLFL_LOAD_FUNCTION(EnableClientStateiEXT);
    GLFL_LOAD_FUNCTION(DisableClientStateiEXT);
    GLFL_LOAD_FUNCTION(GetFloati_vEXT);
    GLFL_LOAD_FUNCTION(GetDoublei_vEXT);
    GLFL_LOAD_FUNCTION(GetPointeri_vEXT);
    GLFL_LOAD_FUNCTION(NamedProgramStringEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4dEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4dvEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4fEXT);
    GLFL_LOAD_FUNCTION(NamedProgramLocalParameter4fvEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterdvEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramLocalParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramivEXT);
    GLFL_LOAD_FUNCTION(GetNamedProgramStringEXT);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageEXT);
    GLFL_LOAD_FUNCTION(GetNamedRenderbufferParameterivEXT);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisampleEXT);
    GLFL_LOAD_FUNCTION(NamedRenderbufferStorageMultisampleCoverageEXT);
    GLFL_LOAD_FUNCTION(CheckNamedFramebufferStatusEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture1DEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture2DEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTexture3DEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferRenderbufferEXT);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferAttachmentParameterivEXT);
    GLFL_LOAD_FUNCTION(GenerateTextureMipmapEXT);
    GLFL_LOAD_FUNCTION(GenerateMultiTexMipmapEXT);
    GLFL_LOAD_FUNCTION(FramebufferDrawBufferEXT);
    GLFL_LOAD_FUNCTION(FramebufferDrawBuffersEXT);
    GLFL_LOAD_FUNCTION(FramebufferReadBufferEXT);
    GLFL_LOAD_FUNCTION(GetFramebufferParameterivEXT);
    GLFL_LOAD_FUNCTION(NamedCopyBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureLayerEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferTextureFaceEXT);
    GLFL_LOAD_FUNCTION(TextureRenderbufferEXT);
    GLFL_LOAD_FUNCTION(MultiTexRenderbufferEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayColorOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayEdgeFlagOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayIndexOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayNormalOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayTexCoordOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayMultiTexCoordOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayFogCoordOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArraySecondaryColorOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribOffsetEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribIOffsetEXT);
    GLFL_LOAD_FUNCTION(EnableVertexArrayEXT);
    GLFL_LOAD_FUNCTION(DisableVertexArrayEXT);
    GLFL_LOAD_FUNCTION(EnableVertexArrayAttribEXT);
    GLFL_LOAD_FUNCTION(DisableVertexArrayAttribEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayIntegervEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayPointervEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayIntegeri_vEXT);
    GLFL_LOAD_FUNCTION(GetVertexArrayPointeri_vEXT);
    GLFL_LOAD_FUNCTION(MapNamedBufferRangeEXT);
    GLFL_LOAD_FUNCTION(FlushMappedNamedBufferRangeEXT);
    GLFL_LOAD_FUNCTION(NamedBufferStorageEXT);
    GLFL_LOAD_FUNCTION(ClearNamedBufferDataEXT);
    GLFL_LOAD_FUNCTION(ClearNamedBufferSubDataEXT);
    GLFL_LOAD_FUNCTION(NamedFramebufferParameteriEXT);
    GLFL_LOAD_FUNCTION(GetNamedFramebufferParameterivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4dEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2dvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3dvEXT);
    GLFL_LOAD_FUNCTION(TextureBufferRangeEXT);
    GLFL_LOAD_FUNCTION(TextureStorage1DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage2DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage3DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage2DMultisampleEXT);
    GLFL_LOAD_FUNCTION(TextureStorage3DMultisampleEXT);
    GLFL_LOAD_FUNCTION(VertexArrayBindVertexBufferEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribFormatEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribIFormatEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribLFormatEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribBindingEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexBindingDivisorEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribLOffsetEXT);
    GLFL_LOAD_FUNCTION(TexturePageCommitmentEXT);
    GLFL_LOAD_FUNCTION(VertexArrayVertexAttribDivisorEXT);
}
void glfl::load_extension_GL_EXT_discard_framebuffer()
{
    GLFL_LOAD_FUNCTION(DiscardFramebufferEXT);
}
void glfl::load_extension_GL_EXT_disjoint_timer_query()
{
    GLFL_LOAD_FUNCTION(GenQueriesEXT);
    GLFL_LOAD_FUNCTION(DeleteQueriesEXT);
    GLFL_LOAD_FUNCTION(IsQueryEXT);
    GLFL_LOAD_FUNCTION(BeginQueryEXT);
    GLFL_LOAD_FUNCTION(EndQueryEXT);
    GLFL_LOAD_FUNCTION(QueryCounterEXT);
    GLFL_LOAD_FUNCTION(GetQueryivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectuivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjecti64vEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectui64vEXT);
}
void glfl::load_extension_GL_EXT_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersEXT);
}
void glfl::load_extension_GL_EXT_draw_buffers2()
{
    GLFL_LOAD_FUNCTION(ColorMaskIndexedEXT);
    GLFL_LOAD_FUNCTION(GetBooleanIndexedvEXT);
    GLFL_LOAD_FUNCTION(GetIntegerIndexedvEXT);
    GLFL_LOAD_FUNCTION(EnableIndexedEXT);
    GLFL_LOAD_FUNCTION(DisableIndexedEXT);
    GLFL_LOAD_FUNCTION(IsEnabledIndexedEXT);
}
void glfl::load_extension_GL_EXT_draw_buffers_indexed()
{
    GLFL_LOAD_FUNCTION(EnableiEXT);
    GLFL_LOAD_FUNCTION(DisableiEXT);
    GLFL_LOAD_FUNCTION(BlendEquationiEXT);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateiEXT);
    GLFL_LOAD_FUNCTION(BlendFunciEXT);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateiEXT);
    GLFL_LOAD_FUNCTION(ColorMaskiEXT);
    GLFL_LOAD_FUNCTION(IsEnablediEXT);
}
void glfl::load_extension_GL_EXT_draw_elements_base_vertex()
{
    GLFL_LOAD_FUNCTION(DrawElementsBaseVertexEXT);
    GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertexEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexEXT);
    GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertexEXT);
}
void glfl::load_extension_GL_EXT_draw_instanced()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedEXT);
}
void glfl::load_extension_GL_EXT_draw_range_elements()
{
    GLFL_LOAD_FUNCTION(DrawRangeElementsEXT);
}
void glfl::load_extension_GL_EXT_draw_transform_feedback()
{
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackEXT);
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackInstancedEXT);
}
void glfl::load_extension_GL_EXT_float_blend() {}
void glfl::load_extension_GL_EXT_fog_coord()
{
    GLFL_LOAD_FUNCTION(FogCoordfEXT);
    GLFL_LOAD_FUNCTION(FogCoordfvEXT);
    GLFL_LOAD_FUNCTION(FogCoorddEXT);
    GLFL_LOAD_FUNCTION(FogCoorddvEXT);
    GLFL_LOAD_FUNCTION(FogCoordPointerEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_blit()
{
    GLFL_LOAD_FUNCTION(BlitFramebufferEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_multisample_blit_scaled() {}
void glfl::load_extension_GL_EXT_framebuffer_object()
{
    GLFL_LOAD_FUNCTION(IsRenderbufferEXT);
    GLFL_LOAD_FUNCTION(BindRenderbufferEXT);
    GLFL_LOAD_FUNCTION(DeleteRenderbuffersEXT);
    GLFL_LOAD_FUNCTION(GenRenderbuffersEXT);
    GLFL_LOAD_FUNCTION(RenderbufferStorageEXT);
    GLFL_LOAD_FUNCTION(GetRenderbufferParameterivEXT);
    GLFL_LOAD_FUNCTION(IsFramebufferEXT);
    GLFL_LOAD_FUNCTION(BindFramebufferEXT);
    GLFL_LOAD_FUNCTION(DeleteFramebuffersEXT);
    GLFL_LOAD_FUNCTION(GenFramebuffersEXT);
    GLFL_LOAD_FUNCTION(CheckFramebufferStatusEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture1DEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture3DEXT);
    GLFL_LOAD_FUNCTION(FramebufferRenderbufferEXT);
    GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameterivEXT);
    GLFL_LOAD_FUNCTION(GenerateMipmapEXT);
}
void glfl::load_extension_GL_EXT_framebuffer_sRGB() {}
void glfl::load_extension_GL_EXT_geometry_point_size() {}
void glfl::load_extension_GL_EXT_geometry_shader()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureEXT);
}
void glfl::load_extension_GL_EXT_geometry_shader4()
{
    GLFL_LOAD_FUNCTION(ProgramParameteriEXT);
}
void glfl::load_extension_GL_EXT_gpu_program_parameters()
{
    GLFL_LOAD_FUNCTION(ProgramEnvParameters4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramLocalParameters4fvEXT);
}
void glfl::load_extension_GL_EXT_gpu_shader4()
{
    GLFL_LOAD_FUNCTION(GetUniformuivEXT);
    GLFL_LOAD_FUNCTION(BindFragDataLocationEXT);
    GLFL_LOAD_FUNCTION(GetFragDataLocationEXT);
    GLFL_LOAD_FUNCTION(Uniform1uiEXT);
    GLFL_LOAD_FUNCTION(Uniform2uiEXT);
    GLFL_LOAD_FUNCTION(Uniform3uiEXT);
    GLFL_LOAD_FUNCTION(Uniform4uiEXT);
    GLFL_LOAD_FUNCTION(Uniform1uivEXT);
    GLFL_LOAD_FUNCTION(Uniform2uivEXT);
    GLFL_LOAD_FUNCTION(Uniform3uivEXT);
    GLFL_LOAD_FUNCTION(Uniform4uivEXT);
}
void glfl::load_extension_GL_EXT_gpu_shader5() {}
void glfl::load_extension_GL_EXT_histogram()
{
    GLFL_LOAD_FUNCTION(GetHistogramEXT);
    GLFL_LOAD_FUNCTION(GetHistogramParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetHistogramParameterivEXT);
    GLFL_LOAD_FUNCTION(GetMinmaxEXT);
    GLFL_LOAD_FUNCTION(GetMinmaxParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetMinmaxParameterivEXT);
    GLFL_LOAD_FUNCTION(HistogramEXT);
    GLFL_LOAD_FUNCTION(MinmaxEXT);
    GLFL_LOAD_FUNCTION(ResetHistogramEXT);
    GLFL_LOAD_FUNCTION(ResetMinmaxEXT);
}
void glfl::load_extension_GL_EXT_index_array_formats() {}
void glfl::load_extension_GL_EXT_index_func()
{
    GLFL_LOAD_FUNCTION(IndexFuncEXT);
}
void glfl::load_extension_GL_EXT_index_material()
{
    GLFL_LOAD_FUNCTION(IndexMaterialEXT);
}
void glfl::load_extension_GL_EXT_index_texture() {}
void glfl::load_extension_GL_EXT_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedEXT);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedEXT);
    GLFL_LOAD_FUNCTION(VertexAttribDivisorEXT);
}
void glfl::load_extension_GL_EXT_light_texture()
{
    GLFL_LOAD_FUNCTION(ApplyTextureEXT);
    GLFL_LOAD_FUNCTION(TextureLightEXT);
    GLFL_LOAD_FUNCTION(TextureMaterialEXT);
}
void glfl::load_extension_GL_EXT_map_buffer_range()
{
    GLFL_LOAD_FUNCTION(MapBufferRangeEXT);
    GLFL_LOAD_FUNCTION(FlushMappedBufferRangeEXT);
}
void glfl::load_extension_GL_EXT_misc_attribute() {}
void glfl::load_extension_GL_EXT_multi_draw_arrays()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysEXT);
    GLFL_LOAD_FUNCTION(MultiDrawElementsEXT);
}
void glfl::load_extension_GL_EXT_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectEXT);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectEXT);
}
void glfl::load_extension_GL_EXT_multisample()
{
    GLFL_LOAD_FUNCTION(SampleMaskEXT);
    GLFL_LOAD_FUNCTION(SamplePatternEXT);
}
void glfl::load_extension_GL_EXT_multisampled_compatibility() {}
void glfl::load_extension_GL_EXT_multisampled_render_to_texture()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleEXT);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DMultisampleEXT);
}
void glfl::load_extension_GL_EXT_multiview_draw_buffers()
{
    GLFL_LOAD_FUNCTION(ReadBufferIndexedEXT);
    GLFL_LOAD_FUNCTION(DrawBuffersIndexedEXT);
    GLFL_LOAD_FUNCTION(GetIntegeri_vEXT);
}
void glfl::load_extension_GL_EXT_occlusion_query_boolean()
{
    GLFL_LOAD_FUNCTION(GenQueriesEXT);
    GLFL_LOAD_FUNCTION(DeleteQueriesEXT);
    GLFL_LOAD_FUNCTION(IsQueryEXT);
    GLFL_LOAD_FUNCTION(BeginQueryEXT);
    GLFL_LOAD_FUNCTION(EndQueryEXT);
    GLFL_LOAD_FUNCTION(GetQueryivEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectuivEXT);
}
void glfl::load_extension_GL_EXT_packed_depth_stencil() {}
void glfl::load_extension_GL_EXT_packed_float() {}
void glfl::load_extension_GL_EXT_packed_pixels() {}
void glfl::load_extension_GL_EXT_paletted_texture()
{
    GLFL_LOAD_FUNCTION(ColorTableEXT);
    GLFL_LOAD_FUNCTION(GetColorTableEXT);
    GLFL_LOAD_FUNCTION(GetColorTableParameterivEXT);
    GLFL_LOAD_FUNCTION(GetColorTableParameterfvEXT);
}
void glfl::load_extension_GL_EXT_pixel_buffer_object() {}
void glfl::load_extension_GL_EXT_pixel_transform()
{
    GLFL_LOAD_FUNCTION(PixelTransformParameteriEXT);
    GLFL_LOAD_FUNCTION(PixelTransformParameterfEXT);
    GLFL_LOAD_FUNCTION(PixelTransformParameterivEXT);
    GLFL_LOAD_FUNCTION(PixelTransformParameterfvEXT);
    GLFL_LOAD_FUNCTION(GetPixelTransformParameterivEXT);
    GLFL_LOAD_FUNCTION(GetPixelTransformParameterfvEXT);
}
void glfl::load_extension_GL_EXT_pixel_transform_color_table() {}
void glfl::load_extension_GL_EXT_point_parameters()
{
    GLFL_LOAD_FUNCTION(PointParameterfEXT);
    GLFL_LOAD_FUNCTION(PointParameterfvEXT);
}
void glfl::load_extension_GL_EXT_polygon_offset()
{
    GLFL_LOAD_FUNCTION(PolygonOffsetEXT);
}
void glfl::load_extension_GL_EXT_polygon_offset_clamp()
{
    GLFL_LOAD_FUNCTION(PolygonOffsetClampEXT);
}
void glfl::load_extension_GL_EXT_post_depth_coverage() {}
void glfl::load_extension_GL_EXT_primitive_bounding_box()
{
    GLFL_LOAD_FUNCTION(PrimitiveBoundingBoxEXT);
}
void glfl::load_extension_GL_EXT_protected_textures() {}
void glfl::load_extension_GL_EXT_provoking_vertex()
{
    GLFL_LOAD_FUNCTION(ProvokingVertexEXT);
}
void glfl::load_extension_GL_EXT_pvrtc_sRGB() {}
void glfl::load_extension_GL_EXT_raster_multisample()
{
    GLFL_LOAD_FUNCTION(RasterSamplesEXT);
}
void glfl::load_extension_GL_EXT_read_format_bgra() {}
void glfl::load_extension_GL_EXT_render_snorm() {}
void glfl::load_extension_GL_EXT_rescale_normal() {}
void glfl::load_extension_GL_EXT_robustness()
{
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatusEXT);
    GLFL_LOAD_FUNCTION(ReadnPixelsEXT);
    GLFL_LOAD_FUNCTION(GetnUniformfvEXT);
    GLFL_LOAD_FUNCTION(GetnUniformivEXT);
}
void glfl::load_extension_GL_EXT_sRGB() {}
void glfl::load_extension_GL_EXT_sRGB_write_control() {}
void glfl::load_extension_GL_EXT_secondary_color()
{
    GLFL_LOAD_FUNCTION(SecondaryColor3bEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3bvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3dEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3dvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3fEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3fvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3iEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3ivEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3sEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3svEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3ubEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3ubvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3uiEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3uivEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3usEXT);
    GLFL_LOAD_FUNCTION(SecondaryColor3usvEXT);
    GLFL_LOAD_FUNCTION(SecondaryColorPointerEXT);
}
void glfl::load_extension_GL_EXT_separate_shader_objects()
{
    GLFL_LOAD_FUNCTION(UseShaderProgramEXT);
    GLFL_LOAD_FUNCTION(ActiveProgramEXT);
    GLFL_LOAD_FUNCTION(CreateShaderProgramEXT);
    GLFL_LOAD_FUNCTION(ActiveShaderProgramEXT);
    GLFL_LOAD_FUNCTION(BindProgramPipelineEXT);
    GLFL_LOAD_FUNCTION(CreateShaderProgramvEXT);
    GLFL_LOAD_FUNCTION(DeleteProgramPipelinesEXT);
    GLFL_LOAD_FUNCTION(GenProgramPipelinesEXT);
    GLFL_LOAD_FUNCTION(GetProgramPipelineInfoLogEXT);
    GLFL_LOAD_FUNCTION(GetProgramPipelineivEXT);
    GLFL_LOAD_FUNCTION(IsProgramPipelineEXT);
    GLFL_LOAD_FUNCTION(ProgramParameteriEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4iEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4ivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fvEXT);
    GLFL_LOAD_FUNCTION(UseProgramStagesEXT);
    GLFL_LOAD_FUNCTION(ValidateProgramPipelineEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uiEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform1uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform2uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform3uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniform4uivEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x3fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix2x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x2fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix3x4fvEXT);
    GLFL_LOAD_FUNCTION(ProgramUniformMatrix4x3fvEXT);
}
void glfl::load_extension_GL_EXT_separate_specular_color() {}
void glfl::load_extension_GL_EXT_shader_framebuffer_fetch() {}
void glfl::load_extension_GL_EXT_shader_group_vote() {}
void glfl::load_extension_GL_EXT_shader_image_load_formatted() {}
void glfl::load_extension_GL_EXT_shader_image_load_store()
{
    GLFL_LOAD_FUNCTION(BindImageTextureEXT);
    GLFL_LOAD_FUNCTION(MemoryBarrierEXT);
}
void glfl::load_extension_GL_EXT_shader_implicit_conversions() {}
void glfl::load_extension_GL_EXT_shader_integer_mix() {}
void glfl::load_extension_GL_EXT_shader_io_blocks() {}
void glfl::load_extension_GL_EXT_shader_non_constant_global_initializers() {}
void glfl::load_extension_GL_EXT_shader_pixel_local_storage() {}
void glfl::load_extension_GL_EXT_shader_pixel_local_storage2()
{
    GLFL_LOAD_FUNCTION(FramebufferPixelLocalStorageSizeEXT);
    GLFL_LOAD_FUNCTION(GetFramebufferPixelLocalStorageSizeEXT);
    GLFL_LOAD_FUNCTION(ClearPixelLocalStorageuiEXT);
}
void glfl::load_extension_GL_EXT_shader_texture_lod() {}
void glfl::load_extension_GL_EXT_shadow_funcs() {}
void glfl::load_extension_GL_EXT_shadow_samplers() {}
void glfl::load_extension_GL_EXT_shared_texture_palette() {}
void glfl::load_extension_GL_EXT_sparse_texture()
{
    GLFL_LOAD_FUNCTION(TexPageCommitmentEXT);
}
void glfl::load_extension_GL_EXT_sparse_texture2() {}
void glfl::load_extension_GL_EXT_stencil_clear_tag()
{
    GLFL_LOAD_FUNCTION(StencilClearTagEXT);
}
void glfl::load_extension_GL_EXT_stencil_two_side()
{
    GLFL_LOAD_FUNCTION(ActiveStencilFaceEXT);
}
void glfl::load_extension_GL_EXT_stencil_wrap() {}
void glfl::load_extension_GL_EXT_subtexture()
{
    GLFL_LOAD_FUNCTION(TexSubImage1DEXT);
    GLFL_LOAD_FUNCTION(TexSubImage2DEXT);
}
void glfl::load_extension_GL_EXT_tessellation_point_size() {}
void glfl::load_extension_GL_EXT_tessellation_shader()
{
    GLFL_LOAD_FUNCTION(PatchParameteriEXT);
}
void glfl::load_extension_GL_EXT_texture() {}
void glfl::load_extension_GL_EXT_texture3D()
{
    GLFL_LOAD_FUNCTION(TexImage3DEXT);
    GLFL_LOAD_FUNCTION(TexSubImage3DEXT);
}
void glfl::load_extension_GL_EXT_texture_array()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerEXT);
}
void glfl::load_extension_GL_EXT_texture_border_clamp()
{
    GLFL_LOAD_FUNCTION(TexParameterIivEXT);
    GLFL_LOAD_FUNCTION(TexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(SamplerParameterIivEXT);
    GLFL_LOAD_FUNCTION(SamplerParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIuivEXT);
}
void glfl::load_extension_GL_EXT_texture_buffer()
{
    GLFL_LOAD_FUNCTION(TexBufferEXT);
    GLFL_LOAD_FUNCTION(TexBufferRangeEXT);
}
void glfl::load_extension_GL_EXT_texture_buffer_object()
{
    GLFL_LOAD_FUNCTION(TexBufferEXT);
}
void glfl::load_extension_GL_EXT_texture_compression_dxt1() {}
void glfl::load_extension_GL_EXT_texture_compression_latc() {}
void glfl::load_extension_GL_EXT_texture_compression_rgtc() {}
void glfl::load_extension_GL_EXT_texture_compression_s3tc() {}
void glfl::load_extension_GL_EXT_texture_cube_map() {}
void glfl::load_extension_GL_EXT_texture_cube_map_array() {}
void glfl::load_extension_GL_EXT_texture_env_add() {}
void glfl::load_extension_GL_EXT_texture_env_combine() {}
void glfl::load_extension_GL_EXT_texture_env_dot3() {}
void glfl::load_extension_GL_EXT_texture_filter_anisotropic() {}
void glfl::load_extension_GL_EXT_texture_filter_minmax()
{
    GLFL_LOAD_FUNCTION(RasterSamplesEXT);
}
void glfl::load_extension_GL_EXT_texture_format_BGRA8888() {}
void glfl::load_extension_GL_EXT_texture_integer()
{
    GLFL_LOAD_FUNCTION(TexParameterIivEXT);
    GLFL_LOAD_FUNCTION(TexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIivEXT);
    GLFL_LOAD_FUNCTION(GetTexParameterIuivEXT);
    GLFL_LOAD_FUNCTION(ClearColorIiEXT);
    GLFL_LOAD_FUNCTION(ClearColorIuiEXT);
}
void glfl::load_extension_GL_EXT_texture_lod_bias() {}
void glfl::load_extension_GL_EXT_texture_mirror_clamp() {}
void glfl::load_extension_GL_EXT_texture_norm16() {}
void glfl::load_extension_GL_EXT_texture_object()
{
    GLFL_LOAD_FUNCTION(AreTexturesResidentEXT);
    GLFL_LOAD_FUNCTION(BindTextureEXT);
    GLFL_LOAD_FUNCTION(DeleteTexturesEXT);
    GLFL_LOAD_FUNCTION(GenTexturesEXT);
    GLFL_LOAD_FUNCTION(IsTextureEXT);
    GLFL_LOAD_FUNCTION(PrioritizeTexturesEXT);
}
void glfl::load_extension_GL_EXT_texture_perturb_normal()
{
    GLFL_LOAD_FUNCTION(TextureNormalEXT);
}
void glfl::load_extension_GL_EXT_texture_rg() {}
void glfl::load_extension_GL_EXT_texture_sRGB() {}
void glfl::load_extension_GL_EXT_texture_sRGB_R8() {}
void glfl::load_extension_GL_EXT_texture_sRGB_RG8() {}
void glfl::load_extension_GL_EXT_texture_sRGB_decode() {}
void glfl::load_extension_GL_EXT_texture_shared_exponent() {}
void glfl::load_extension_GL_EXT_texture_snorm() {}
void glfl::load_extension_GL_EXT_texture_storage()
{
    GLFL_LOAD_FUNCTION(TexStorage1DEXT);
    GLFL_LOAD_FUNCTION(TexStorage2DEXT);
    GLFL_LOAD_FUNCTION(TexStorage3DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage1DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage2DEXT);
    GLFL_LOAD_FUNCTION(TextureStorage3DEXT);
}
void glfl::load_extension_GL_EXT_texture_swizzle() {}
void glfl::load_extension_GL_EXT_texture_type_2_10_10_10_REV() {}
void glfl::load_extension_GL_EXT_texture_view()
{
    GLFL_LOAD_FUNCTION(TextureViewEXT);
}
void glfl::load_extension_GL_EXT_timer_query()
{
    GLFL_LOAD_FUNCTION(GetQueryObjecti64vEXT);
    GLFL_LOAD_FUNCTION(GetQueryObjectui64vEXT);
}
void glfl::load_extension_GL_EXT_transform_feedback()
{
    GLFL_LOAD_FUNCTION(BeginTransformFeedbackEXT);
    GLFL_LOAD_FUNCTION(EndTransformFeedbackEXT);
    GLFL_LOAD_FUNCTION(BindBufferRangeEXT);
    GLFL_LOAD_FUNCTION(BindBufferOffsetEXT);
    GLFL_LOAD_FUNCTION(BindBufferBaseEXT);
    GLFL_LOAD_FUNCTION(TransformFeedbackVaryingsEXT);
    GLFL_LOAD_FUNCTION(GetTransformFeedbackVaryingEXT);
}
void glfl::load_extension_GL_EXT_unpack_subimage() {}
void glfl::load_extension_GL_EXT_vertex_array()
{
    GLFL_LOAD_FUNCTION(ArrayElementEXT);
    GLFL_LOAD_FUNCTION(ColorPointerEXT);
    GLFL_LOAD_FUNCTION(DrawArraysEXT);
    GLFL_LOAD_FUNCTION(EdgeFlagPointerEXT);
    GLFL_LOAD_FUNCTION(GetPointervEXT);
    GLFL_LOAD_FUNCTION(IndexPointerEXT);
    GLFL_LOAD_FUNCTION(NormalPointerEXT);
    GLFL_LOAD_FUNCTION(TexCoordPointerEXT);
    GLFL_LOAD_FUNCTION(VertexPointerEXT);
}
void glfl::load_extension_GL_EXT_vertex_array_bgra() {}
void glfl::load_extension_GL_EXT_vertex_attrib_64bit()
{
    GLFL_LOAD_FUNCTION(VertexAttribL1dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL2dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL3dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL4dEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL1dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL2dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL3dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribL4dvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribLPointerEXT);
    GLFL_LOAD_FUNCTION(GetVertexAttribLdvEXT);
}
void glfl::load_extension_GL_EXT_vertex_shader()
{
    GLFL_LOAD_FUNCTION(BeginVertexShaderEXT);
    GLFL_LOAD_FUNCTION(EndVertexShaderEXT);
    GLFL_LOAD_FUNCTION(BindVertexShaderEXT);
    GLFL_LOAD_FUNCTION(GenVertexShadersEXT);
    GLFL_LOAD_FUNCTION(DeleteVertexShaderEXT);
    GLFL_LOAD_FUNCTION(ShaderOp1EXT);
    GLFL_LOAD_FUNCTION(ShaderOp2EXT);
    GLFL_LOAD_FUNCTION(ShaderOp3EXT);
    GLFL_LOAD_FUNCTION(SwizzleEXT);
    GLFL_LOAD_FUNCTION(WriteMaskEXT);
    GLFL_LOAD_FUNCTION(InsertComponentEXT);
    GLFL_LOAD_FUNCTION(ExtractComponentEXT);
    GLFL_LOAD_FUNCTION(GenSymbolsEXT);
    GLFL_LOAD_FUNCTION(SetInvariantEXT);
    GLFL_LOAD_FUNCTION(SetLocalConstantEXT);
    GLFL_LOAD_FUNCTION(VariantbvEXT);
    GLFL_LOAD_FUNCTION(VariantsvEXT);
    GLFL_LOAD_FUNCTION(VariantivEXT);
    GLFL_LOAD_FUNCTION(VariantfvEXT);
    GLFL_LOAD_FUNCTION(VariantdvEXT);
    GLFL_LOAD_FUNCTION(VariantubvEXT);
    GLFL_LOAD_FUNCTION(VariantusvEXT);
    GLFL_LOAD_FUNCTION(VariantuivEXT);
    GLFL_LOAD_FUNCTION(VariantPointerEXT);
    GLFL_LOAD_FUNCTION(EnableVariantClientStateEXT);
    GLFL_LOAD_FUNCTION(DisableVariantClientStateEXT);
    GLFL_LOAD_FUNCTION(BindLightParameterEXT);
    GLFL_LOAD_FUNCTION(BindMaterialParameterEXT);
    GLFL_LOAD_FUNCTION(BindTexGenParameterEXT);
    GLFL_LOAD_FUNCTION(BindTextureUnitParameterEXT);
    GLFL_LOAD_FUNCTION(BindParameterEXT);
    GLFL_LOAD_FUNCTION(IsVariantEnabledEXT);
    GLFL_LOAD_FUNCTION(GetVariantBooleanvEXT);
    GLFL_LOAD_FUNCTION(GetVariantIntegervEXT);
    GLFL_LOAD_FUNCTION(GetVariantFloatvEXT);
    GLFL_LOAD_FUNCTION(GetVariantPointervEXT);
    GLFL_LOAD_FUNCTION(GetInvariantBooleanvEXT);
    GLFL_LOAD_FUNCTION(GetInvariantIntegervEXT);
    GLFL_LOAD_FUNCTION(GetInvariantFloatvEXT);
    GLFL_LOAD_FUNCTION(GetLocalConstantBooleanvEXT);
    GLFL_LOAD_FUNCTION(GetLocalConstantIntegervEXT);
    GLFL_LOAD_FUNCTION(GetLocalConstantFloatvEXT);
}
void glfl::load_extension_GL_EXT_vertex_weighting()
{
    GLFL_LOAD_FUNCTION(VertexWeightfEXT);
    GLFL_LOAD_FUNCTION(VertexWeightfvEXT);
    GLFL_LOAD_FUNCTION(VertexWeightPointerEXT);
}
void glfl::load_extension_GL_EXT_window_rectangles()
{
    GLFL_LOAD_FUNCTION(WindowRectanglesEXT);
}
void glfl::load_extension_GL_EXT_x11_sync_object()
{
    GLFL_LOAD_FUNCTION(ImportSyncEXT);
}
void glfl::load_extension_GL_FJ_shader_binary_GCCSO() {}
void glfl::load_extension_GL_GREMEDY_frame_terminator()
{
    GLFL_LOAD_FUNCTION(FrameTerminatorGREMEDY);
}
void glfl::load_extension_GL_GREMEDY_string_marker()
{
    GLFL_LOAD_FUNCTION(StringMarkerGREMEDY);
}
void glfl::load_extension_GL_HP_convolution_border_modes() {}
void glfl::load_extension_GL_HP_image_transform()
{
    GLFL_LOAD_FUNCTION(ImageTransformParameteriHP);
    GLFL_LOAD_FUNCTION(ImageTransformParameterfHP);
    GLFL_LOAD_FUNCTION(ImageTransformParameterivHP);
    GLFL_LOAD_FUNCTION(ImageTransformParameterfvHP);
    GLFL_LOAD_FUNCTION(GetImageTransformParameterivHP);
    GLFL_LOAD_FUNCTION(GetImageTransformParameterfvHP);
}
void glfl::load_extension_GL_HP_occlusion_test() {}
void glfl::load_extension_GL_HP_texture_lighting() {}
void glfl::load_extension_GL_IBM_cull_vertex() {}
void glfl::load_extension_GL_IBM_multimode_draw_arrays()
{
    GLFL_LOAD_FUNCTION(MultiModeDrawArraysIBM);
    GLFL_LOAD_FUNCTION(MultiModeDrawElementsIBM);
}
void glfl::load_extension_GL_IBM_rasterpos_clip() {}
void glfl::load_extension_GL_IBM_static_data()
{
    GLFL_LOAD_FUNCTION(FlushStaticDataIBM);
}
void glfl::load_extension_GL_IBM_texture_mirrored_repeat() {}
void glfl::load_extension_GL_IBM_vertex_array_lists()
{
    GLFL_LOAD_FUNCTION(ColorPointerListIBM);
    GLFL_LOAD_FUNCTION(SecondaryColorPointerListIBM);
    GLFL_LOAD_FUNCTION(EdgeFlagPointerListIBM);
    GLFL_LOAD_FUNCTION(FogCoordPointerListIBM);
    GLFL_LOAD_FUNCTION(IndexPointerListIBM);
    GLFL_LOAD_FUNCTION(NormalPointerListIBM);
    GLFL_LOAD_FUNCTION(TexCoordPointerListIBM);
    GLFL_LOAD_FUNCTION(VertexPointerListIBM);
}
void glfl::load_extension_GL_IMG_bindless_texture()
{
    GLFL_LOAD_FUNCTION(GetTextureHandleIMG);
    GLFL_LOAD_FUNCTION(GetTextureSamplerHandleIMG);
    GLFL_LOAD_FUNCTION(UniformHandleui64IMG);
    GLFL_LOAD_FUNCTION(UniformHandleui64vIMG);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64IMG);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64vIMG);
}
void glfl::load_extension_GL_IMG_framebuffer_downsample()
{
    GLFL_LOAD_FUNCTION(FramebufferTexture2DDownsampleIMG);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerDownsampleIMG);
}
void glfl::load_extension_GL_IMG_multisampled_render_to_texture()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleIMG);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DMultisampleIMG);
}
void glfl::load_extension_GL_IMG_program_binary() {}
void glfl::load_extension_GL_IMG_read_format() {}
void glfl::load_extension_GL_IMG_shader_binary() {}
void glfl::load_extension_GL_IMG_texture_compression_pvrtc() {}
void glfl::load_extension_GL_IMG_texture_compression_pvrtc2() {}
void glfl::load_extension_GL_IMG_texture_env_enhanced_fixed_function() {}
void glfl::load_extension_GL_IMG_texture_filter_cubic() {}
void glfl::load_extension_GL_IMG_user_clip_plane()
{
    GLFL_LOAD_FUNCTION(ClipPlanefIMG);
    GLFL_LOAD_FUNCTION(ClipPlanexIMG);
}
void glfl::load_extension_GL_INGR_blend_func_separate()
{
    GLFL_LOAD_FUNCTION(BlendFuncSeparateINGR);
}
void glfl::load_extension_GL_INGR_color_clamp() {}
void glfl::load_extension_GL_INGR_interlace_read() {}
void glfl::load_extension_GL_INTEL_conservative_rasterization() {}
void glfl::load_extension_GL_INTEL_fragment_shader_ordering() {}
void glfl::load_extension_GL_INTEL_framebuffer_CMAA()
{
    GLFL_LOAD_FUNCTION(ApplyFramebufferAttachmentCMAAINTEL);
}
void glfl::load_extension_GL_INTEL_map_texture()
{
    GLFL_LOAD_FUNCTION(SyncTextureINTEL);
    GLFL_LOAD_FUNCTION(UnmapTexture2DINTEL);
    GLFL_LOAD_FUNCTION(MapTexture2DINTEL);
}
void glfl::load_extension_GL_INTEL_parallel_arrays()
{
    GLFL_LOAD_FUNCTION(VertexPointervINTEL);
    GLFL_LOAD_FUNCTION(NormalPointervINTEL);
    GLFL_LOAD_FUNCTION(ColorPointervINTEL);
    GLFL_LOAD_FUNCTION(TexCoordPointervINTEL);
}
void glfl::load_extension_GL_INTEL_performance_query()
{
    GLFL_LOAD_FUNCTION(BeginPerfQueryINTEL);
    GLFL_LOAD_FUNCTION(CreatePerfQueryINTEL);
    GLFL_LOAD_FUNCTION(DeletePerfQueryINTEL);
    GLFL_LOAD_FUNCTION(EndPerfQueryINTEL);
    GLFL_LOAD_FUNCTION(GetFirstPerfQueryIdINTEL);
    GLFL_LOAD_FUNCTION(GetNextPerfQueryIdINTEL);
    GLFL_LOAD_FUNCTION(GetPerfCounterInfoINTEL);
    GLFL_LOAD_FUNCTION(GetPerfQueryDataINTEL);
    GLFL_LOAD_FUNCTION(GetPerfQueryIdByNameINTEL);
    GLFL_LOAD_FUNCTION(GetPerfQueryInfoINTEL);
}
void glfl::load_extension_GL_KHR_blend_equation_advanced()
{
    GLFL_LOAD_FUNCTION(BlendBarrierKHR);
}
void glfl::load_extension_GL_KHR_blend_equation_advanced_coherent() {}
void glfl::load_extension_GL_KHR_context_flush_control() {}
void glfl::load_extension_GL_KHR_debug()
{
    GLFL_LOAD_FUNCTION(DebugMessageControl);
    GLFL_LOAD_FUNCTION(DebugMessageInsert);
    GLFL_LOAD_FUNCTION(DebugMessageCallback);
    GLFL_LOAD_FUNCTION(GetDebugMessageLog);
    GLFL_LOAD_FUNCTION(PushDebugGroup);
    GLFL_LOAD_FUNCTION(PopDebugGroup);
    GLFL_LOAD_FUNCTION(ObjectLabel);
    GLFL_LOAD_FUNCTION(GetObjectLabel);
    GLFL_LOAD_FUNCTION(ObjectPtrLabel);
    GLFL_LOAD_FUNCTION(GetObjectPtrLabel);
    GLFL_LOAD_FUNCTION(GetPointerv);
    GLFL_LOAD_FUNCTION(DebugMessageControlKHR);
    GLFL_LOAD_FUNCTION(DebugMessageInsertKHR);
    GLFL_LOAD_FUNCTION(DebugMessageCallbackKHR);
    GLFL_LOAD_FUNCTION(GetDebugMessageLogKHR);
    GLFL_LOAD_FUNCTION(PushDebugGroupKHR);
    GLFL_LOAD_FUNCTION(PopDebugGroupKHR);
    GLFL_LOAD_FUNCTION(ObjectLabelKHR);
    GLFL_LOAD_FUNCTION(GetObjectLabelKHR);
    GLFL_LOAD_FUNCTION(ObjectPtrLabelKHR);
    GLFL_LOAD_FUNCTION(GetObjectPtrLabelKHR);
    GLFL_LOAD_FUNCTION(GetPointervKHR);
}
void glfl::load_extension_GL_KHR_no_error() {}
void glfl::load_extension_GL_KHR_robust_buffer_access_behavior() {}
void glfl::load_extension_GL_KHR_robustness()
{
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatus);
    GLFL_LOAD_FUNCTION(ReadnPixels);
    GLFL_LOAD_FUNCTION(GetnUniformfv);
    GLFL_LOAD_FUNCTION(GetnUniformiv);
    GLFL_LOAD_FUNCTION(GetnUniformuiv);
    GLFL_LOAD_FUNCTION(GetGraphicsResetStatusKHR);
    GLFL_LOAD_FUNCTION(ReadnPixelsKHR);
    GLFL_LOAD_FUNCTION(GetnUniformfvKHR);
    GLFL_LOAD_FUNCTION(GetnUniformivKHR);
    GLFL_LOAD_FUNCTION(GetnUniformuivKHR);
}
void glfl::load_extension_GL_KHR_texture_compression_astc_hdr() {}
void glfl::load_extension_GL_KHR_texture_compression_astc_ldr() {}
void glfl::load_extension_GL_KHR_texture_compression_astc_sliced_3d() {}
void glfl::load_extension_GL_MESAX_texture_stack() {}
void glfl::load_extension_GL_MESA_pack_invert() {}
void glfl::load_extension_GL_MESA_resize_buffers()
{
    GLFL_LOAD_FUNCTION(ResizeBuffersMESA);
}
void glfl::load_extension_GL_MESA_window_pos()
{
    GLFL_LOAD_FUNCTION(WindowPos2dMESA);
    GLFL_LOAD_FUNCTION(WindowPos2dvMESA);
    GLFL_LOAD_FUNCTION(WindowPos2fMESA);
    GLFL_LOAD_FUNCTION(WindowPos2fvMESA);
    GLFL_LOAD_FUNCTION(WindowPos2iMESA);
    GLFL_LOAD_FUNCTION(WindowPos2ivMESA);
    GLFL_LOAD_FUNCTION(WindowPos2sMESA);
    GLFL_LOAD_FUNCTION(WindowPos2svMESA);
    GLFL_LOAD_FUNCTION(WindowPos3dMESA);
    GLFL_LOAD_FUNCTION(WindowPos3dvMESA);
    GLFL_LOAD_FUNCTION(WindowPos3fMESA);
    GLFL_LOAD_FUNCTION(WindowPos3fvMESA);
    GLFL_LOAD_FUNCTION(WindowPos3iMESA);
    GLFL_LOAD_FUNCTION(WindowPos3ivMESA);
    GLFL_LOAD_FUNCTION(WindowPos3sMESA);
    GLFL_LOAD_FUNCTION(WindowPos3svMESA);
    GLFL_LOAD_FUNCTION(WindowPos4dMESA);
    GLFL_LOAD_FUNCTION(WindowPos4dvMESA);
    GLFL_LOAD_FUNCTION(WindowPos4fMESA);
    GLFL_LOAD_FUNCTION(WindowPos4fvMESA);
    GLFL_LOAD_FUNCTION(WindowPos4iMESA);
    GLFL_LOAD_FUNCTION(WindowPos4ivMESA);
    GLFL_LOAD_FUNCTION(WindowPos4sMESA);
    GLFL_LOAD_FUNCTION(WindowPos4svMESA);
}
void glfl::load_extension_GL_MESA_ycbcr_texture() {}
void glfl::load_extension_GL_NVX_conditional_render()
{
    GLFL_LOAD_FUNCTION(BeginConditionalRenderNVX);
    GLFL_LOAD_FUNCTION(EndConditionalRenderNVX);
}
void glfl::load_extension_GL_NVX_gpu_memory_info() {}
void glfl::load_extension_GL_NV_bindless_multi_draw_indirect()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectBindlessNV);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectBindlessNV);
}
void glfl::load_extension_GL_NV_bindless_multi_draw_indirect_count()
{
    GLFL_LOAD_FUNCTION(MultiDrawArraysIndirectBindlessCountNV);
    GLFL_LOAD_FUNCTION(MultiDrawElementsIndirectBindlessCountNV);
}
void glfl::load_extension_GL_NV_bindless_texture()
{
    GLFL_LOAD_FUNCTION(GetTextureHandleNV);
    GLFL_LOAD_FUNCTION(GetTextureSamplerHandleNV);
    GLFL_LOAD_FUNCTION(MakeTextureHandleResidentNV);
    GLFL_LOAD_FUNCTION(MakeTextureHandleNonResidentNV);
    GLFL_LOAD_FUNCTION(GetImageHandleNV);
    GLFL_LOAD_FUNCTION(MakeImageHandleResidentNV);
    GLFL_LOAD_FUNCTION(MakeImageHandleNonResidentNV);
    GLFL_LOAD_FUNCTION(UniformHandleui64NV);
    GLFL_LOAD_FUNCTION(UniformHandleui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniformHandleui64vNV);
    GLFL_LOAD_FUNCTION(IsTextureHandleResidentNV);
    GLFL_LOAD_FUNCTION(IsImageHandleResidentNV);
}
void glfl::load_extension_GL_NV_blend_equation_advanced()
{
    GLFL_LOAD_FUNCTION(BlendParameteriNV);
    GLFL_LOAD_FUNCTION(BlendBarrierNV);
}
void glfl::load_extension_GL_NV_blend_equation_advanced_coherent() {}
void glfl::load_extension_GL_NV_blend_square() {}
void glfl::load_extension_GL_NV_clip_space_w_scaling()
{
    GLFL_LOAD_FUNCTION(ViewportPositionWScaleNV);
}
void glfl::load_extension_GL_NV_command_list()
{
    GLFL_LOAD_FUNCTION(CreateStatesNV);
    GLFL_LOAD_FUNCTION(DeleteStatesNV);
    GLFL_LOAD_FUNCTION(IsStateNV);
    GLFL_LOAD_FUNCTION(StateCaptureNV);
    GLFL_LOAD_FUNCTION(GetCommandHeaderNV);
    GLFL_LOAD_FUNCTION(GetStageIndexNV);
    GLFL_LOAD_FUNCTION(DrawCommandsNV);
    GLFL_LOAD_FUNCTION(DrawCommandsAddressNV);
    GLFL_LOAD_FUNCTION(DrawCommandsStatesNV);
    GLFL_LOAD_FUNCTION(DrawCommandsStatesAddressNV);
    GLFL_LOAD_FUNCTION(CreateCommandListsNV);
    GLFL_LOAD_FUNCTION(DeleteCommandListsNV);
    GLFL_LOAD_FUNCTION(IsCommandListNV);
    GLFL_LOAD_FUNCTION(ListDrawCommandsStatesClientNV);
    GLFL_LOAD_FUNCTION(CommandListSegmentsNV);
    GLFL_LOAD_FUNCTION(CompileCommandListNV);
    GLFL_LOAD_FUNCTION(CallCommandListNV);
}
void glfl::load_extension_GL_NV_compute_program5() {}
void glfl::load_extension_GL_NV_conditional_render()
{
    GLFL_LOAD_FUNCTION(BeginConditionalRenderNV);
    GLFL_LOAD_FUNCTION(EndConditionalRenderNV);
}
void glfl::load_extension_GL_NV_conservative_raster()
{
    GLFL_LOAD_FUNCTION(SubpixelPrecisionBiasNV);
}
void glfl::load_extension_GL_NV_conservative_raster_dilate()
{
    GLFL_LOAD_FUNCTION(ConservativeRasterParameterfNV);
}
void glfl::load_extension_GL_NV_conservative_raster_pre_snap_triangles()
{
    GLFL_LOAD_FUNCTION(ConservativeRasterParameteriNV);
}
void glfl::load_extension_GL_NV_copy_buffer()
{
    GLFL_LOAD_FUNCTION(CopyBufferSubDataNV);
}
void glfl::load_extension_GL_NV_copy_depth_to_color() {}
void glfl::load_extension_GL_NV_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubDataNV);
}
void glfl::load_extension_GL_NV_coverage_sample()
{
    GLFL_LOAD_FUNCTION(CoverageMaskNV);
    GLFL_LOAD_FUNCTION(CoverageOperationNV);
}
void glfl::load_extension_GL_NV_deep_texture3D() {}
void glfl::load_extension_GL_NV_depth_buffer_float()
{
    GLFL_LOAD_FUNCTION(DepthRangedNV);
    GLFL_LOAD_FUNCTION(ClearDepthdNV);
    GLFL_LOAD_FUNCTION(DepthBoundsdNV);
}
void glfl::load_extension_GL_NV_depth_clamp() {}
void glfl::load_extension_GL_NV_depth_nonlinear() {}
void glfl::load_extension_GL_NV_draw_buffers()
{
    GLFL_LOAD_FUNCTION(DrawBuffersNV);
}
void glfl::load_extension_GL_NV_draw_instanced()
{
    GLFL_LOAD_FUNCTION(DrawArraysInstancedNV);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedNV);
}
void glfl::load_extension_GL_NV_draw_texture()
{
    GLFL_LOAD_FUNCTION(DrawTextureNV);
}
void glfl::load_extension_GL_NV_evaluators()
{
    GLFL_LOAD_FUNCTION(MapControlPointsNV);
    GLFL_LOAD_FUNCTION(MapParameterivNV);
    GLFL_LOAD_FUNCTION(MapParameterfvNV);
    GLFL_LOAD_FUNCTION(GetMapControlPointsNV);
    GLFL_LOAD_FUNCTION(GetMapParameterivNV);
    GLFL_LOAD_FUNCTION(GetMapParameterfvNV);
    GLFL_LOAD_FUNCTION(GetMapAttribParameterivNV);
    GLFL_LOAD_FUNCTION(GetMapAttribParameterfvNV);
    GLFL_LOAD_FUNCTION(EvalMapsNV);
}
void glfl::load_extension_GL_NV_explicit_attrib_location() {}
void glfl::load_extension_GL_NV_explicit_multisample()
{
    GLFL_LOAD_FUNCTION(GetMultisamplefvNV);
    GLFL_LOAD_FUNCTION(SampleMaskIndexedNV);
    GLFL_LOAD_FUNCTION(TexRenderbufferNV);
}
void glfl::load_extension_GL_NV_fbo_color_attachments() {}
void glfl::load_extension_GL_NV_fence()
{
    GLFL_LOAD_FUNCTION(DeleteFencesNV);
    GLFL_LOAD_FUNCTION(GenFencesNV);
    GLFL_LOAD_FUNCTION(IsFenceNV);
    GLFL_LOAD_FUNCTION(TestFenceNV);
    GLFL_LOAD_FUNCTION(GetFenceivNV);
    GLFL_LOAD_FUNCTION(FinishFenceNV);
    GLFL_LOAD_FUNCTION(SetFenceNV);
}
void glfl::load_extension_GL_NV_fill_rectangle() {}
void glfl::load_extension_GL_NV_float_buffer() {}
void glfl::load_extension_GL_NV_fog_distance() {}
void glfl::load_extension_GL_NV_fragment_coverage_to_color()
{
    GLFL_LOAD_FUNCTION(FragmentCoverageColorNV);
}
void glfl::load_extension_GL_NV_fragment_program()
{
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4fNV);
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4fvNV);
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4dNV);
    GLFL_LOAD_FUNCTION(ProgramNamedParameter4dvNV);
    GLFL_LOAD_FUNCTION(GetProgramNamedParameterfvNV);
    GLFL_LOAD_FUNCTION(GetProgramNamedParameterdvNV);
}
void glfl::load_extension_GL_NV_fragment_program2() {}
void glfl::load_extension_GL_NV_fragment_program4() {}
void glfl::load_extension_GL_NV_fragment_program_option() {}
void glfl::load_extension_GL_NV_fragment_shader_interlock() {}
void glfl::load_extension_GL_NV_framebuffer_blit()
{
    GLFL_LOAD_FUNCTION(BlitFramebufferNV);
}
void glfl::load_extension_GL_NV_framebuffer_mixed_samples()
{
    GLFL_LOAD_FUNCTION(RasterSamplesEXT);
    GLFL_LOAD_FUNCTION(CoverageModulationTableNV);
    GLFL_LOAD_FUNCTION(GetCoverageModulationTableNV);
    GLFL_LOAD_FUNCTION(CoverageModulationNV);
}
void glfl::load_extension_GL_NV_framebuffer_multisample()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleNV);
}
void glfl::load_extension_GL_NV_framebuffer_multisample_coverage()
{
    GLFL_LOAD_FUNCTION(RenderbufferStorageMultisampleCoverageNV);
}
void glfl::load_extension_GL_NV_generate_mipmap_sRGB() {}
void glfl::load_extension_GL_NV_geometry_program4()
{
    GLFL_LOAD_FUNCTION(ProgramVertexLimitNV);
    GLFL_LOAD_FUNCTION(FramebufferTextureEXT);
    GLFL_LOAD_FUNCTION(FramebufferTextureLayerEXT);
    GLFL_LOAD_FUNCTION(FramebufferTextureFaceEXT);
}
void glfl::load_extension_GL_NV_geometry_shader4() {}
void glfl::load_extension_GL_NV_geometry_shader_passthrough() {}
void glfl::load_extension_GL_NV_gpu_program4()
{
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4iNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParametersI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4uiNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParameterI4uivNV);
    GLFL_LOAD_FUNCTION(ProgramLocalParametersI4uivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4iNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParametersI4ivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4uiNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParameterI4uivNV);
    GLFL_LOAD_FUNCTION(ProgramEnvParametersI4uivNV);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterIivNV);
    GLFL_LOAD_FUNCTION(GetProgramLocalParameterIuivNV);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterIivNV);
    GLFL_LOAD_FUNCTION(GetProgramEnvParameterIuivNV);
}
void glfl::load_extension_GL_NV_gpu_program5()
{
    GLFL_LOAD_FUNCTION(ProgramSubroutineParametersuivNV);
    GLFL_LOAD_FUNCTION(GetProgramSubroutineParameteruivNV);
}
void glfl::load_extension_GL_NV_gpu_program5_mem_extended() {}
void glfl::load_extension_GL_NV_gpu_shader5()
{
    GLFL_LOAD_FUNCTION(Uniform1i64NV);
    GLFL_LOAD_FUNCTION(Uniform2i64NV);
    GLFL_LOAD_FUNCTION(Uniform3i64NV);
    GLFL_LOAD_FUNCTION(Uniform4i64NV);
    GLFL_LOAD_FUNCTION(Uniform1i64vNV);
    GLFL_LOAD_FUNCTION(Uniform2i64vNV);
    GLFL_LOAD_FUNCTION(Uniform3i64vNV);
    GLFL_LOAD_FUNCTION(Uniform4i64vNV);
    GLFL_LOAD_FUNCTION(Uniform1ui64NV);
    GLFL_LOAD_FUNCTION(Uniform2ui64NV);
    GLFL_LOAD_FUNCTION(Uniform3ui64NV);
    GLFL_LOAD_FUNCTION(Uniform4ui64NV);
    GLFL_LOAD_FUNCTION(Uniform1ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform2ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform3ui64vNV);
    GLFL_LOAD_FUNCTION(Uniform4ui64vNV);
    GLFL_LOAD_FUNCTION(GetUniformi64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4i64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniform1ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform2ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform3ui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniform4ui64vNV);
}
void glfl::load_extension_GL_NV_half_float()
{
    GLFL_LOAD_FUNCTION(Vertex2hNV);
    GLFL_LOAD_FUNCTION(Vertex2hvNV);
    GLFL_LOAD_FUNCTION(Vertex3hNV);
    GLFL_LOAD_FUNCTION(Vertex3hvNV);
    GLFL_LOAD_FUNCTION(Vertex4hNV);
    GLFL_LOAD_FUNCTION(Vertex4hvNV);
    GLFL_LOAD_FUNCTION(Normal3hNV);
    GLFL_LOAD_FUNCTION(Normal3hvNV);
    GLFL_LOAD_FUNCTION(Color3hNV);
    GLFL_LOAD_FUNCTION(Color3hvNV);
    GLFL_LOAD_FUNCTION(Color4hNV);
    GLFL_LOAD_FUNCTION(Color4hvNV);
    GLFL_LOAD_FUNCTION(TexCoord1hNV);
    GLFL_LOAD_FUNCTION(TexCoord1hvNV);
    GLFL_LOAD_FUNCTION(TexCoord2hNV);
    GLFL_LOAD_FUNCTION(TexCoord2hvNV);
    GLFL_LOAD_FUNCTION(TexCoord3hNV);
    GLFL_LOAD_FUNCTION(TexCoord3hvNV);
    GLFL_LOAD_FUNCTION(TexCoord4hNV);
    GLFL_LOAD_FUNCTION(TexCoord4hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord1hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord1hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord2hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord2hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord3hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord3hvNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord4hNV);
    GLFL_LOAD_FUNCTION(MultiTexCoord4hvNV);
    GLFL_LOAD_FUNCTION(FogCoordhNV);
    GLFL_LOAD_FUNCTION(FogCoordhvNV);
    GLFL_LOAD_FUNCTION(SecondaryColor3hNV);
    GLFL_LOAD_FUNCTION(SecondaryColor3hvNV);
    GLFL_LOAD_FUNCTION(VertexWeighthNV);
    GLFL_LOAD_FUNCTION(VertexWeighthvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1hvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2hvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3hvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4hNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3hvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4hvNV);
}
void glfl::load_extension_GL_NV_image_formats() {}
void glfl::load_extension_GL_NV_instanced_arrays()
{
    GLFL_LOAD_FUNCTION(VertexAttribDivisorNV);
}
void glfl::load_extension_GL_NV_internalformat_sample_query()
{
    GLFL_LOAD_FUNCTION(GetInternalformatSampleivNV);
}
void glfl::load_extension_GL_NV_light_max_exponent() {}
void glfl::load_extension_GL_NV_multisample_coverage() {}
void glfl::load_extension_GL_NV_multisample_filter_hint() {}
void glfl::load_extension_GL_NV_non_square_matrices()
{
    GLFL_LOAD_FUNCTION(UniformMatrix2x3fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix3x2fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix2x4fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix4x2fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix3x4fvNV);
    GLFL_LOAD_FUNCTION(UniformMatrix4x3fvNV);
}
void glfl::load_extension_GL_NV_occlusion_query()
{
    GLFL_LOAD_FUNCTION(GenOcclusionQueriesNV);
    GLFL_LOAD_FUNCTION(DeleteOcclusionQueriesNV);
    GLFL_LOAD_FUNCTION(IsOcclusionQueryNV);
    GLFL_LOAD_FUNCTION(BeginOcclusionQueryNV);
    GLFL_LOAD_FUNCTION(EndOcclusionQueryNV);
    GLFL_LOAD_FUNCTION(GetOcclusionQueryivNV);
    GLFL_LOAD_FUNCTION(GetOcclusionQueryuivNV);
}
void glfl::load_extension_GL_NV_packed_depth_stencil() {}
void glfl::load_extension_GL_NV_parameter_buffer_object()
{
    GLFL_LOAD_FUNCTION(ProgramBufferParametersfvNV);
    GLFL_LOAD_FUNCTION(ProgramBufferParametersIivNV);
    GLFL_LOAD_FUNCTION(ProgramBufferParametersIuivNV);
}
void glfl::load_extension_GL_NV_parameter_buffer_object2() {}
void glfl::load_extension_GL_NV_path_rendering()
{
    GLFL_LOAD_FUNCTION(GenPathsNV);
    GLFL_LOAD_FUNCTION(DeletePathsNV);
    GLFL_LOAD_FUNCTION(IsPathNV);
    GLFL_LOAD_FUNCTION(PathCommandsNV);
    GLFL_LOAD_FUNCTION(PathCoordsNV);
    GLFL_LOAD_FUNCTION(PathSubCommandsNV);
    GLFL_LOAD_FUNCTION(PathSubCoordsNV);
    GLFL_LOAD_FUNCTION(PathStringNV);
    GLFL_LOAD_FUNCTION(PathGlyphsNV);
    GLFL_LOAD_FUNCTION(PathGlyphRangeNV);
    GLFL_LOAD_FUNCTION(WeightPathsNV);
    GLFL_LOAD_FUNCTION(CopyPathNV);
    GLFL_LOAD_FUNCTION(InterpolatePathsNV);
    GLFL_LOAD_FUNCTION(TransformPathNV);
    GLFL_LOAD_FUNCTION(PathParameterivNV);
    GLFL_LOAD_FUNCTION(PathParameteriNV);
    GLFL_LOAD_FUNCTION(PathParameterfvNV);
    GLFL_LOAD_FUNCTION(PathParameterfNV);
    GLFL_LOAD_FUNCTION(PathDashArrayNV);
    GLFL_LOAD_FUNCTION(PathStencilFuncNV);
    GLFL_LOAD_FUNCTION(PathStencilDepthOffsetNV);
    GLFL_LOAD_FUNCTION(StencilFillPathNV);
    GLFL_LOAD_FUNCTION(StencilStrokePathNV);
    GLFL_LOAD_FUNCTION(StencilFillPathInstancedNV);
    GLFL_LOAD_FUNCTION(StencilStrokePathInstancedNV);
    GLFL_LOAD_FUNCTION(PathCoverDepthFuncNV);
    GLFL_LOAD_FUNCTION(CoverFillPathNV);
    GLFL_LOAD_FUNCTION(CoverStrokePathNV);
    GLFL_LOAD_FUNCTION(CoverFillPathInstancedNV);
    GLFL_LOAD_FUNCTION(CoverStrokePathInstancedNV);
    GLFL_LOAD_FUNCTION(GetPathParameterivNV);
    GLFL_LOAD_FUNCTION(GetPathParameterfvNV);
    GLFL_LOAD_FUNCTION(GetPathCommandsNV);
    GLFL_LOAD_FUNCTION(GetPathCoordsNV);
    GLFL_LOAD_FUNCTION(GetPathDashArrayNV);
    GLFL_LOAD_FUNCTION(GetPathMetricsNV);
    GLFL_LOAD_FUNCTION(GetPathMetricRangeNV);
    GLFL_LOAD_FUNCTION(GetPathSpacingNV);
    GLFL_LOAD_FUNCTION(IsPointInFillPathNV);
    GLFL_LOAD_FUNCTION(IsPointInStrokePathNV);
    GLFL_LOAD_FUNCTION(GetPathLengthNV);
    GLFL_LOAD_FUNCTION(PointAlongPathNV);
    GLFL_LOAD_FUNCTION(MatrixLoad3x2fNV);
    GLFL_LOAD_FUNCTION(MatrixLoad3x3fNV);
    GLFL_LOAD_FUNCTION(MatrixLoadTranspose3x3fNV);
    GLFL_LOAD_FUNCTION(MatrixMult3x2fNV);
    GLFL_LOAD_FUNCTION(MatrixMult3x3fNV);
    GLFL_LOAD_FUNCTION(MatrixMultTranspose3x3fNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverFillPathNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverStrokePathNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverFillPathInstancedNV);
    GLFL_LOAD_FUNCTION(StencilThenCoverStrokePathInstancedNV);
    GLFL_LOAD_FUNCTION(PathGlyphIndexRangeNV);
    GLFL_LOAD_FUNCTION(PathGlyphIndexArrayNV);
    GLFL_LOAD_FUNCTION(PathMemoryGlyphIndexArrayNV);
    GLFL_LOAD_FUNCTION(ProgramPathFragmentInputGenNV);
    GLFL_LOAD_FUNCTION(GetProgramResourcefvNV);
    GLFL_LOAD_FUNCTION(PathColorGenNV);
    GLFL_LOAD_FUNCTION(PathTexGenNV);
    GLFL_LOAD_FUNCTION(PathFogGenNV);
    GLFL_LOAD_FUNCTION(GetPathColorGenivNV);
    GLFL_LOAD_FUNCTION(GetPathColorGenfvNV);
    GLFL_LOAD_FUNCTION(GetPathTexGenivNV);
    GLFL_LOAD_FUNCTION(GetPathTexGenfvNV);
}
void glfl::load_extension_GL_NV_path_rendering_shared_edge() {}
void glfl::load_extension_GL_NV_pixel_data_range()
{
    GLFL_LOAD_FUNCTION(PixelDataRangeNV);
    GLFL_LOAD_FUNCTION(FlushPixelDataRangeNV);
}
void glfl::load_extension_GL_NV_point_sprite()
{
    GLFL_LOAD_FUNCTION(PointParameteriNV);
    GLFL_LOAD_FUNCTION(PointParameterivNV);
}
void glfl::load_extension_GL_NV_polygon_mode()
{
    GLFL_LOAD_FUNCTION(PolygonModeNV);
}
void glfl::load_extension_GL_NV_present_video()
{
    GLFL_LOAD_FUNCTION(PresentFrameKeyedNV);
    GLFL_LOAD_FUNCTION(PresentFrameDualFillNV);
    GLFL_LOAD_FUNCTION(GetVideoivNV);
    GLFL_LOAD_FUNCTION(GetVideouivNV);
    GLFL_LOAD_FUNCTION(GetVideoi64vNV);
    GLFL_LOAD_FUNCTION(GetVideoui64vNV);
}
void glfl::load_extension_GL_NV_primitive_restart()
{
    GLFL_LOAD_FUNCTION(PrimitiveRestartNV);
    GLFL_LOAD_FUNCTION(PrimitiveRestartIndexNV);
}
void glfl::load_extension_GL_NV_read_buffer()
{
    GLFL_LOAD_FUNCTION(ReadBufferNV);
}
void glfl::load_extension_GL_NV_read_buffer_front() {}
void glfl::load_extension_GL_NV_read_depth() {}
void glfl::load_extension_GL_NV_read_depth_stencil() {}
void glfl::load_extension_GL_NV_read_stencil() {}
void glfl::load_extension_GL_NV_register_combiners()
{
    GLFL_LOAD_FUNCTION(CombinerParameterfvNV);
    GLFL_LOAD_FUNCTION(CombinerParameterfNV);
    GLFL_LOAD_FUNCTION(CombinerParameterivNV);
    GLFL_LOAD_FUNCTION(CombinerParameteriNV);
    GLFL_LOAD_FUNCTION(CombinerInputNV);
    GLFL_LOAD_FUNCTION(CombinerOutputNV);
    GLFL_LOAD_FUNCTION(FinalCombinerInputNV);
    GLFL_LOAD_FUNCTION(GetCombinerInputParameterfvNV);
    GLFL_LOAD_FUNCTION(GetCombinerInputParameterivNV);
    GLFL_LOAD_FUNCTION(GetCombinerOutputParameterfvNV);
    GLFL_LOAD_FUNCTION(GetCombinerOutputParameterivNV);
    GLFL_LOAD_FUNCTION(GetFinalCombinerInputParameterfvNV);
    GLFL_LOAD_FUNCTION(GetFinalCombinerInputParameterivNV);
}
void glfl::load_extension_GL_NV_register_combiners2()
{
    GLFL_LOAD_FUNCTION(CombinerStageParameterfvNV);
    GLFL_LOAD_FUNCTION(GetCombinerStageParameterfvNV);
}
void glfl::load_extension_GL_NV_robustness_video_memory_purge() {}
void glfl::load_extension_GL_NV_sRGB_formats() {}
void glfl::load_extension_GL_NV_sample_locations()
{
    GLFL_LOAD_FUNCTION(FramebufferSampleLocationsfvNV);
    GLFL_LOAD_FUNCTION(NamedFramebufferSampleLocationsfvNV);
    GLFL_LOAD_FUNCTION(ResolveDepthValuesNV);
}
void glfl::load_extension_GL_NV_sample_mask_override_coverage() {}
void glfl::load_extension_GL_NV_shader_atomic_counters() {}
void glfl::load_extension_GL_NV_shader_atomic_float() {}
void glfl::load_extension_GL_NV_shader_atomic_float64() {}
void glfl::load_extension_GL_NV_shader_atomic_fp16_vector() {}
void glfl::load_extension_GL_NV_shader_atomic_int64() {}
void glfl::load_extension_GL_NV_shader_buffer_load()
{
    GLFL_LOAD_FUNCTION(MakeBufferResidentNV);
    GLFL_LOAD_FUNCTION(MakeBufferNonResidentNV);
    GLFL_LOAD_FUNCTION(IsBufferResidentNV);
    GLFL_LOAD_FUNCTION(MakeNamedBufferResidentNV);
    GLFL_LOAD_FUNCTION(MakeNamedBufferNonResidentNV);
    GLFL_LOAD_FUNCTION(IsNamedBufferResidentNV);
    GLFL_LOAD_FUNCTION(GetBufferParameterui64vNV);
    GLFL_LOAD_FUNCTION(GetNamedBufferParameterui64vNV);
    GLFL_LOAD_FUNCTION(GetIntegerui64vNV);
    GLFL_LOAD_FUNCTION(Uniformui64NV);
    GLFL_LOAD_FUNCTION(Uniformui64vNV);
    GLFL_LOAD_FUNCTION(GetUniformui64vNV);
    GLFL_LOAD_FUNCTION(ProgramUniformui64NV);
    GLFL_LOAD_FUNCTION(ProgramUniformui64vNV);
}
void glfl::load_extension_GL_NV_shader_buffer_store() {}
void glfl::load_extension_GL_NV_shader_noperspective_interpolation() {}
void glfl::load_extension_GL_NV_shader_storage_buffer_object() {}
void glfl::load_extension_GL_NV_shader_thread_group() {}
void glfl::load_extension_GL_NV_shader_thread_shuffle() {}
void glfl::load_extension_GL_NV_shadow_samplers_array() {}
void glfl::load_extension_GL_NV_shadow_samplers_cube() {}
void glfl::load_extension_GL_NV_stereo_view_rendering() {}
void glfl::load_extension_GL_NV_tessellation_program5() {}
void glfl::load_extension_GL_NV_texgen_emboss() {}
void glfl::load_extension_GL_NV_texgen_reflection() {}
void glfl::load_extension_GL_NV_texture_barrier()
{
    GLFL_LOAD_FUNCTION(TextureBarrierNV);
}
void glfl::load_extension_GL_NV_texture_border_clamp() {}
void glfl::load_extension_GL_NV_texture_compression_s3tc_update() {}
void glfl::load_extension_GL_NV_texture_compression_vtc() {}
void glfl::load_extension_GL_NV_texture_env_combine4() {}
void glfl::load_extension_GL_NV_texture_expand_normal() {}
void glfl::load_extension_GL_NV_texture_multisample()
{
    GLFL_LOAD_FUNCTION(TexImage2DMultisampleCoverageNV);
    GLFL_LOAD_FUNCTION(TexImage3DMultisampleCoverageNV);
    GLFL_LOAD_FUNCTION(TextureImage2DMultisampleNV);
    GLFL_LOAD_FUNCTION(TextureImage3DMultisampleNV);
    GLFL_LOAD_FUNCTION(TextureImage2DMultisampleCoverageNV);
    GLFL_LOAD_FUNCTION(TextureImage3DMultisampleCoverageNV);
}
void glfl::load_extension_GL_NV_texture_npot_2D_mipmap() {}
void glfl::load_extension_GL_NV_texture_rectangle() {}
void glfl::load_extension_GL_NV_texture_shader() {}
void glfl::load_extension_GL_NV_texture_shader2() {}
void glfl::load_extension_GL_NV_texture_shader3() {}
void glfl::load_extension_GL_NV_transform_feedback()
{
    GLFL_LOAD_FUNCTION(BeginTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(EndTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(TransformFeedbackAttribsNV);
    GLFL_LOAD_FUNCTION(BindBufferRangeNV);
    GLFL_LOAD_FUNCTION(BindBufferOffsetNV);
    GLFL_LOAD_FUNCTION(BindBufferBaseNV);
    GLFL_LOAD_FUNCTION(TransformFeedbackVaryingsNV);
    GLFL_LOAD_FUNCTION(ActiveVaryingNV);
    GLFL_LOAD_FUNCTION(GetVaryingLocationNV);
    GLFL_LOAD_FUNCTION(GetActiveVaryingNV);
    GLFL_LOAD_FUNCTION(GetTransformFeedbackVaryingNV);
    GLFL_LOAD_FUNCTION(TransformFeedbackStreamAttribsNV);
}
void glfl::load_extension_GL_NV_transform_feedback2()
{
    GLFL_LOAD_FUNCTION(BindTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(DeleteTransformFeedbacksNV);
    GLFL_LOAD_FUNCTION(GenTransformFeedbacksNV);
    GLFL_LOAD_FUNCTION(IsTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(PauseTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(ResumeTransformFeedbackNV);
    GLFL_LOAD_FUNCTION(DrawTransformFeedbackNV);
}
void glfl::load_extension_GL_NV_uniform_buffer_unified_memory() {}
void glfl::load_extension_GL_NV_vdpau_interop()
{
    GLFL_LOAD_FUNCTION(VDPAUInitNV);
    GLFL_LOAD_FUNCTION(VDPAUFiniNV);
    GLFL_LOAD_FUNCTION(VDPAURegisterVideoSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAURegisterOutputSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAUIsSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAUUnregisterSurfaceNV);
    GLFL_LOAD_FUNCTION(VDPAUGetSurfaceivNV);
    GLFL_LOAD_FUNCTION(VDPAUSurfaceAccessNV);
    GLFL_LOAD_FUNCTION(VDPAUMapSurfacesNV);
    GLFL_LOAD_FUNCTION(VDPAUUnmapSurfacesNV);
}
void glfl::load_extension_GL_NV_vertex_array_range()
{
    GLFL_LOAD_FUNCTION(FlushVertexArrayRangeNV);
    GLFL_LOAD_FUNCTION(VertexArrayRangeNV);
}
void glfl::load_extension_GL_NV_vertex_array_range2() {}
void glfl::load_extension_GL_NV_vertex_attrib_integer_64bit()
{
    GLFL_LOAD_FUNCTION(VertexAttribL1i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL2i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL3i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL4i64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL1i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL2i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL3i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL4i64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL2ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL3ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL4ui64NV);
    GLFL_LOAD_FUNCTION(VertexAttribL1ui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL2ui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL3ui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribL4ui64vNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribLi64vNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribLui64vNV);
    GLFL_LOAD_FUNCTION(VertexAttribLFormatNV);
}
void glfl::load_extension_GL_NV_vertex_buffer_unified_memory()
{
    GLFL_LOAD_FUNCTION(BufferAddressRangeNV);
    GLFL_LOAD_FUNCTION(VertexFormatNV);
    GLFL_LOAD_FUNCTION(NormalFormatNV);
    GLFL_LOAD_FUNCTION(ColorFormatNV);
    GLFL_LOAD_FUNCTION(IndexFormatNV);
    GLFL_LOAD_FUNCTION(TexCoordFormatNV);
    GLFL_LOAD_FUNCTION(EdgeFlagFormatNV);
    GLFL_LOAD_FUNCTION(SecondaryColorFormatNV);
    GLFL_LOAD_FUNCTION(FogCoordFormatNV);
    GLFL_LOAD_FUNCTION(VertexAttribFormatNV);
    GLFL_LOAD_FUNCTION(VertexAttribIFormatNV);
    GLFL_LOAD_FUNCTION(GetIntegerui64i_vNV);
}
void glfl::load_extension_GL_NV_vertex_program()
{
    GLFL_LOAD_FUNCTION(AreProgramsResidentNV);
    GLFL_LOAD_FUNCTION(BindProgramNV);
    GLFL_LOAD_FUNCTION(DeleteProgramsNV);
    GLFL_LOAD_FUNCTION(ExecuteProgramNV);
    GLFL_LOAD_FUNCTION(GenProgramsNV);
    GLFL_LOAD_FUNCTION(GetProgramParameterdvNV);
    GLFL_LOAD_FUNCTION(GetProgramParameterfvNV);
    GLFL_LOAD_FUNCTION(GetProgramivNV);
    GLFL_LOAD_FUNCTION(GetProgramStringNV);
    GLFL_LOAD_FUNCTION(GetTrackMatrixivNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribdvNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribfvNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribivNV);
    GLFL_LOAD_FUNCTION(GetVertexAttribPointervNV);
    GLFL_LOAD_FUNCTION(IsProgramNV);
    GLFL_LOAD_FUNCTION(LoadProgramNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4dNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4dvNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4fNV);
    GLFL_LOAD_FUNCTION(ProgramParameter4fvNV);
    GLFL_LOAD_FUNCTION(ProgramParameters4dvNV);
    GLFL_LOAD_FUNCTION(ProgramParameters4fvNV);
    GLFL_LOAD_FUNCTION(RequestResidentProgramsNV);
    GLFL_LOAD_FUNCTION(TrackMatrixNV);
    GLFL_LOAD_FUNCTION(VertexAttribPointerNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib1svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib2svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib3svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4dNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4dvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4fNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4fvNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4sNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4svNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubNV);
    GLFL_LOAD_FUNCTION(VertexAttrib4ubvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs1svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs2svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs3svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4dvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4fvNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4svNV);
    GLFL_LOAD_FUNCTION(VertexAttribs4ubvNV);
}
void glfl::load_extension_GL_NV_vertex_program1_1() {}
void glfl::load_extension_GL_NV_vertex_program2() {}
void glfl::load_extension_GL_NV_vertex_program2_option() {}
void glfl::load_extension_GL_NV_vertex_program3() {}
void glfl::load_extension_GL_NV_vertex_program4()
{
    GLFL_LOAD_FUNCTION(VertexAttribI1iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4iEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI1uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4uiEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI1ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4ivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI1uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI2uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI3uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4uivEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4bvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4svEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4ubvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribI4usvEXT);
    GLFL_LOAD_FUNCTION(VertexAttribIPointerEXT);
    GLFL_LOAD_FUNCTION(GetVertexAttribIivEXT);
    GLFL_LOAD_FUNCTION(GetVertexAttribIuivEXT);
}
void glfl::load_extension_GL_NV_video_capture()
{
    GLFL_LOAD_FUNCTION(BeginVideoCaptureNV);
    GLFL_LOAD_FUNCTION(BindVideoCaptureStreamBufferNV);
    GLFL_LOAD_FUNCTION(BindVideoCaptureStreamTextureNV);
    GLFL_LOAD_FUNCTION(EndVideoCaptureNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureivNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureStreamivNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureStreamfvNV);
    GLFL_LOAD_FUNCTION(GetVideoCaptureStreamdvNV);
    GLFL_LOAD_FUNCTION(VideoCaptureNV);
    GLFL_LOAD_FUNCTION(VideoCaptureStreamParameterivNV);
    GLFL_LOAD_FUNCTION(VideoCaptureStreamParameterfvNV);
    GLFL_LOAD_FUNCTION(VideoCaptureStreamParameterdvNV);
}
void glfl::load_extension_GL_NV_viewport_array()
{
    GLFL_LOAD_FUNCTION(ViewportArrayvNV);
    GLFL_LOAD_FUNCTION(ViewportIndexedfNV);
    GLFL_LOAD_FUNCTION(ViewportIndexedfvNV);
    GLFL_LOAD_FUNCTION(ScissorArrayvNV);
    GLFL_LOAD_FUNCTION(ScissorIndexedNV);
    GLFL_LOAD_FUNCTION(ScissorIndexedvNV);
    GLFL_LOAD_FUNCTION(DepthRangeArrayfvNV);
    GLFL_LOAD_FUNCTION(DepthRangeIndexedfNV);
    GLFL_LOAD_FUNCTION(GetFloati_vNV);
    GLFL_LOAD_FUNCTION(EnableiNV);
    GLFL_LOAD_FUNCTION(DisableiNV);
    GLFL_LOAD_FUNCTION(IsEnablediNV);
}
void glfl::load_extension_GL_NV_viewport_array2() {}
void glfl::load_extension_GL_NV_viewport_swizzle()
{
    GLFL_LOAD_FUNCTION(ViewportSwizzleNV);
}
void glfl::load_extension_GL_OES_EGL_image()
{
    GLFL_LOAD_FUNCTION(EGLImageTargetTexture2DOES);
    GLFL_LOAD_FUNCTION(EGLImageTargetRenderbufferStorageOES);
}
void glfl::load_extension_GL_OES_EGL_image_external() {}
void glfl::load_extension_GL_OES_EGL_image_external_essl3() {}
void glfl::load_extension_GL_OES_blend_equation_separate()
{
    GLFL_LOAD_FUNCTION(BlendEquationSeparateOES);
}
void glfl::load_extension_GL_OES_blend_func_separate()
{
    GLFL_LOAD_FUNCTION(BlendFuncSeparateOES);
}
void glfl::load_extension_GL_OES_blend_subtract()
{
    GLFL_LOAD_FUNCTION(BlendEquationOES);
}
void glfl::load_extension_GL_OES_byte_coordinates()
{
    GLFL_LOAD_FUNCTION(MultiTexCoord1bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord1bvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2bvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3bvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4bOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4bvOES);
    GLFL_LOAD_FUNCTION(TexCoord1bOES);
    GLFL_LOAD_FUNCTION(TexCoord1bvOES);
    GLFL_LOAD_FUNCTION(TexCoord2bOES);
    GLFL_LOAD_FUNCTION(TexCoord2bvOES);
    GLFL_LOAD_FUNCTION(TexCoord3bOES);
    GLFL_LOAD_FUNCTION(TexCoord3bvOES);
    GLFL_LOAD_FUNCTION(TexCoord4bOES);
    GLFL_LOAD_FUNCTION(TexCoord4bvOES);
    GLFL_LOAD_FUNCTION(Vertex2bOES);
    GLFL_LOAD_FUNCTION(Vertex2bvOES);
    GLFL_LOAD_FUNCTION(Vertex3bOES);
    GLFL_LOAD_FUNCTION(Vertex3bvOES);
    GLFL_LOAD_FUNCTION(Vertex4bOES);
    GLFL_LOAD_FUNCTION(Vertex4bvOES);
}
void glfl::load_extension_GL_OES_compressed_ETC1_RGB8_sub_texture() {}
void glfl::load_extension_GL_OES_compressed_ETC1_RGB8_texture() {}
void glfl::load_extension_GL_OES_compressed_paletted_texture() {}
void glfl::load_extension_GL_OES_copy_image()
{
    GLFL_LOAD_FUNCTION(CopyImageSubDataOES);
}
void glfl::load_extension_GL_OES_depth24() {}
void glfl::load_extension_GL_OES_depth32() {}
void glfl::load_extension_GL_OES_depth_texture() {}
void glfl::load_extension_GL_OES_draw_buffers_indexed()
{
    GLFL_LOAD_FUNCTION(EnableiOES);
    GLFL_LOAD_FUNCTION(DisableiOES);
    GLFL_LOAD_FUNCTION(BlendEquationiOES);
    GLFL_LOAD_FUNCTION(BlendEquationSeparateiOES);
    GLFL_LOAD_FUNCTION(BlendFunciOES);
    GLFL_LOAD_FUNCTION(BlendFuncSeparateiOES);
    GLFL_LOAD_FUNCTION(ColorMaskiOES);
    GLFL_LOAD_FUNCTION(IsEnablediOES);
}
void glfl::load_extension_GL_OES_draw_elements_base_vertex()
{
    GLFL_LOAD_FUNCTION(DrawElementsBaseVertexOES);
    GLFL_LOAD_FUNCTION(DrawRangeElementsBaseVertexOES);
    GLFL_LOAD_FUNCTION(DrawElementsInstancedBaseVertexOES);
    GLFL_LOAD_FUNCTION(MultiDrawElementsBaseVertexOES);
}
void glfl::load_extension_GL_OES_draw_texture()
{
    GLFL_LOAD_FUNCTION(DrawTexsOES);
    GLFL_LOAD_FUNCTION(DrawTexiOES);
    GLFL_LOAD_FUNCTION(DrawTexxOES);
    GLFL_LOAD_FUNCTION(DrawTexsvOES);
    GLFL_LOAD_FUNCTION(DrawTexivOES);
    GLFL_LOAD_FUNCTION(DrawTexxvOES);
    GLFL_LOAD_FUNCTION(DrawTexfOES);
    GLFL_LOAD_FUNCTION(DrawTexfvOES);
}
void glfl::load_extension_GL_OES_element_index_uint() {}
void glfl::load_extension_GL_OES_extended_matrix_palette() {}
void glfl::load_extension_GL_OES_fbo_render_mipmap() {}
void glfl::load_extension_GL_OES_fixed_point()
{
    GLFL_LOAD_FUNCTION(AlphaFuncxOES);
    GLFL_LOAD_FUNCTION(ClearColorxOES);
    GLFL_LOAD_FUNCTION(ClearDepthxOES);
    GLFL_LOAD_FUNCTION(ClipPlanexOES);
    GLFL_LOAD_FUNCTION(Color4xOES);
    GLFL_LOAD_FUNCTION(DepthRangexOES);
    GLFL_LOAD_FUNCTION(FogxOES);
    GLFL_LOAD_FUNCTION(FogxvOES);
    GLFL_LOAD_FUNCTION(FrustumxOES);
    GLFL_LOAD_FUNCTION(GetClipPlanexOES);
    GLFL_LOAD_FUNCTION(GetFixedvOES);
    GLFL_LOAD_FUNCTION(GetTexEnvxvOES);
    GLFL_LOAD_FUNCTION(GetTexParameterxvOES);
    GLFL_LOAD_FUNCTION(LightModelxOES);
    GLFL_LOAD_FUNCTION(LightModelxvOES);
    GLFL_LOAD_FUNCTION(LightxOES);
    GLFL_LOAD_FUNCTION(LightxvOES);
    GLFL_LOAD_FUNCTION(LineWidthxOES);
    GLFL_LOAD_FUNCTION(LoadMatrixxOES);
    GLFL_LOAD_FUNCTION(MaterialxOES);
    GLFL_LOAD_FUNCTION(MaterialxvOES);
    GLFL_LOAD_FUNCTION(MultMatrixxOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4xOES);
    GLFL_LOAD_FUNCTION(Normal3xOES);
    GLFL_LOAD_FUNCTION(OrthoxOES);
    GLFL_LOAD_FUNCTION(PointParameterxvOES);
    GLFL_LOAD_FUNCTION(PointSizexOES);
    GLFL_LOAD_FUNCTION(PolygonOffsetxOES);
    GLFL_LOAD_FUNCTION(RotatexOES);
    GLFL_LOAD_FUNCTION(ScalexOES);
    GLFL_LOAD_FUNCTION(TexEnvxOES);
    GLFL_LOAD_FUNCTION(TexEnvxvOES);
    GLFL_LOAD_FUNCTION(TexParameterxOES);
    GLFL_LOAD_FUNCTION(TexParameterxvOES);
    GLFL_LOAD_FUNCTION(TranslatexOES);
    GLFL_LOAD_FUNCTION(GetLightxvOES);
    GLFL_LOAD_FUNCTION(GetMaterialxvOES);
    GLFL_LOAD_FUNCTION(PointParameterxOES);
    GLFL_LOAD_FUNCTION(SampleCoveragexOES);
    GLFL_LOAD_FUNCTION(AccumxOES);
    GLFL_LOAD_FUNCTION(BitmapxOES);
    GLFL_LOAD_FUNCTION(BlendColorxOES);
    GLFL_LOAD_FUNCTION(ClearAccumxOES);
    GLFL_LOAD_FUNCTION(Color3xOES);
    GLFL_LOAD_FUNCTION(Color3xvOES);
    GLFL_LOAD_FUNCTION(Color4xvOES);
    GLFL_LOAD_FUNCTION(ConvolutionParameterxOES);
    GLFL_LOAD_FUNCTION(ConvolutionParameterxvOES);
    GLFL_LOAD_FUNCTION(EvalCoord1xOES);
    GLFL_LOAD_FUNCTION(EvalCoord1xvOES);
    GLFL_LOAD_FUNCTION(EvalCoord2xOES);
    GLFL_LOAD_FUNCTION(EvalCoord2xvOES);
    GLFL_LOAD_FUNCTION(FeedbackBufferxOES);
    GLFL_LOAD_FUNCTION(GetConvolutionParameterxvOES);
    GLFL_LOAD_FUNCTION(GetHistogramParameterxvOES);
    GLFL_LOAD_FUNCTION(GetLightxOES);
    GLFL_LOAD_FUNCTION(GetMapxvOES);
    GLFL_LOAD_FUNCTION(GetMaterialxOES);
    GLFL_LOAD_FUNCTION(GetPixelMapxv);
    GLFL_LOAD_FUNCTION(GetTexGenxvOES);
    GLFL_LOAD_FUNCTION(GetTexLevelParameterxvOES);
    GLFL_LOAD_FUNCTION(IndexxOES);
    GLFL_LOAD_FUNCTION(IndexxvOES);
    GLFL_LOAD_FUNCTION(LoadTransposeMatrixxOES);
    GLFL_LOAD_FUNCTION(Map1xOES);
    GLFL_LOAD_FUNCTION(Map2xOES);
    GLFL_LOAD_FUNCTION(MapGrid1xOES);
    GLFL_LOAD_FUNCTION(MapGrid2xOES);
    GLFL_LOAD_FUNCTION(MultTransposeMatrixxOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord1xOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord1xvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2xOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord2xvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3xOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord3xvOES);
    GLFL_LOAD_FUNCTION(MultiTexCoord4xvOES);
    GLFL_LOAD_FUNCTION(Normal3xvOES);
    GLFL_LOAD_FUNCTION(PassThroughxOES);
    GLFL_LOAD_FUNCTION(PixelMapx);
    GLFL_LOAD_FUNCTION(PixelStorex);
    GLFL_LOAD_FUNCTION(PixelTransferxOES);
    GLFL_LOAD_FUNCTION(PixelZoomxOES);
    GLFL_LOAD_FUNCTION(PrioritizeTexturesxOES);
    GLFL_LOAD_FUNCTION(RasterPos2xOES);
    GLFL_LOAD_FUNCTION(RasterPos2xvOES);
    GLFL_LOAD_FUNCTION(RasterPos3xOES);
    GLFL_LOAD_FUNCTION(RasterPos3xvOES);
    GLFL_LOAD_FUNCTION(RasterPos4xOES);
    GLFL_LOAD_FUNCTION(RasterPos4xvOES);
    GLFL_LOAD_FUNCTION(RectxOES);
    GLFL_LOAD_FUNCTION(RectxvOES);
    GLFL_LOAD_FUNCTION(TexCoord1xOES);
    GLFL_LOAD_FUNCTION(TexCoord1xvOES);
    GLFL_LOAD_FUNCTION(TexCoord2xOES);
    GLFL_LOAD_FUNCTION(TexCoord2xvOES);
    GLFL_LOAD_FUNCTION(TexCoord3xOES);
    GLFL_LOAD_FUNCTION(TexCoord3xvOES);
    GLFL_LOAD_FUNCTION(TexCoord4xOES);
    GLFL_LOAD_FUNCTION(TexCoord4xvOES);
    GLFL_LOAD_FUNCTION(TexGenxOES);
    GLFL_LOAD_FUNCTION(TexGenxvOES);
    GLFL_LOAD_FUNCTION(Vertex2xOES);
    GLFL_LOAD_FUNCTION(Vertex2xvOES);
    GLFL_LOAD_FUNCTION(Vertex3xOES);
    GLFL_LOAD_FUNCTION(Vertex3xvOES);
    GLFL_LOAD_FUNCTION(Vertex4xOES);
    GLFL_LOAD_FUNCTION(Vertex4xvOES);
}
void glfl::load_extension_GL_OES_fragment_precision_high() {}
void glfl::load_extension_GL_OES_framebuffer_object()
{
    GLFL_LOAD_FUNCTION(IsRenderbufferOES);
    GLFL_LOAD_FUNCTION(BindRenderbufferOES);
    GLFL_LOAD_FUNCTION(DeleteRenderbuffersOES);
    GLFL_LOAD_FUNCTION(GenRenderbuffersOES);
    GLFL_LOAD_FUNCTION(RenderbufferStorageOES);
    GLFL_LOAD_FUNCTION(GetRenderbufferParameterivOES);
    GLFL_LOAD_FUNCTION(IsFramebufferOES);
    GLFL_LOAD_FUNCTION(BindFramebufferOES);
    GLFL_LOAD_FUNCTION(DeleteFramebuffersOES);
    GLFL_LOAD_FUNCTION(GenFramebuffersOES);
    GLFL_LOAD_FUNCTION(CheckFramebufferStatusOES);
    GLFL_LOAD_FUNCTION(FramebufferRenderbufferOES);
    GLFL_LOAD_FUNCTION(FramebufferTexture2DOES);
    GLFL_LOAD_FUNCTION(GetFramebufferAttachmentParameterivOES);
    GLFL_LOAD_FUNCTION(GenerateMipmapOES);
}
void glfl::load_extension_GL_OES_geometry_point_size() {}
void glfl::load_extension_GL_OES_geometry_shader()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureOES);
}
void glfl::load_extension_GL_OES_get_program_binary()
{
    GLFL_LOAD_FUNCTION(GetProgramBinaryOES);
    GLFL_LOAD_FUNCTION(ProgramBinaryOES);
}
void glfl::load_extension_GL_OES_gpu_shader5() {}
void glfl::load_extension_GL_OES_mapbuffer()
{
    GLFL_LOAD_FUNCTION(MapBufferOES);
    GLFL_LOAD_FUNCTION(UnmapBufferOES);
    GLFL_LOAD_FUNCTION(GetBufferPointervOES);
}
void glfl::load_extension_GL_OES_matrix_get() {}
void glfl::load_extension_GL_OES_matrix_palette()
{
    GLFL_LOAD_FUNCTION(CurrentPaletteMatrixOES);
    GLFL_LOAD_FUNCTION(LoadPaletteFromModelViewMatrixOES);
    GLFL_LOAD_FUNCTION(MatrixIndexPointerOES);
    GLFL_LOAD_FUNCTION(WeightPointerOES);
}
void glfl::load_extension_GL_OES_packed_depth_stencil() {}
void glfl::load_extension_GL_OES_point_size_array()
{
    GLFL_LOAD_FUNCTION(PointSizePointerOES);
}
void glfl::load_extension_GL_OES_point_sprite() {}
void glfl::load_extension_GL_OES_primitive_bounding_box()
{
    GLFL_LOAD_FUNCTION(PrimitiveBoundingBoxOES);
}
void glfl::load_extension_GL_OES_query_matrix()
{
    GLFL_LOAD_FUNCTION(QueryMatrixxOES);
}
void glfl::load_extension_GL_OES_read_format() {}
void glfl::load_extension_GL_OES_required_internalformat() {}
void glfl::load_extension_GL_OES_rgb8_rgba8() {}
void glfl::load_extension_GL_OES_sample_shading()
{
    GLFL_LOAD_FUNCTION(MinSampleShadingOES);
}
void glfl::load_extension_GL_OES_sample_variables() {}
void glfl::load_extension_GL_OES_shader_image_atomic() {}
void glfl::load_extension_GL_OES_shader_io_blocks() {}
void glfl::load_extension_GL_OES_shader_multisample_interpolation() {}
void glfl::load_extension_GL_OES_single_precision()
{
    GLFL_LOAD_FUNCTION(ClearDepthfOES);
    GLFL_LOAD_FUNCTION(ClipPlanefOES);
    GLFL_LOAD_FUNCTION(DepthRangefOES);
    GLFL_LOAD_FUNCTION(FrustumfOES);
    GLFL_LOAD_FUNCTION(GetClipPlanefOES);
    GLFL_LOAD_FUNCTION(OrthofOES);
}
void glfl::load_extension_GL_OES_standard_derivatives() {}
void glfl::load_extension_GL_OES_stencil1() {}
void glfl::load_extension_GL_OES_stencil4() {}
void glfl::load_extension_GL_OES_stencil8() {}
void glfl::load_extension_GL_OES_stencil_wrap() {}
void glfl::load_extension_GL_OES_surfaceless_context() {}
void glfl::load_extension_GL_OES_tessellation_point_size() {}
void glfl::load_extension_GL_OES_tessellation_shader()
{
    GLFL_LOAD_FUNCTION(PatchParameteriOES);
}
void glfl::load_extension_GL_OES_texture_3D()
{
    GLFL_LOAD_FUNCTION(TexImage3DOES);
    GLFL_LOAD_FUNCTION(TexSubImage3DOES);
    GLFL_LOAD_FUNCTION(CopyTexSubImage3DOES);
    GLFL_LOAD_FUNCTION(CompressedTexImage3DOES);
    GLFL_LOAD_FUNCTION(CompressedTexSubImage3DOES);
    GLFL_LOAD_FUNCTION(FramebufferTexture3DOES);
}
void glfl::load_extension_GL_OES_texture_border_clamp()
{
    GLFL_LOAD_FUNCTION(TexParameterIivOES);
    GLFL_LOAD_FUNCTION(TexParameterIuivOES);
    GLFL_LOAD_FUNCTION(GetTexParameterIivOES);
    GLFL_LOAD_FUNCTION(GetTexParameterIuivOES);
    GLFL_LOAD_FUNCTION(SamplerParameterIivOES);
    GLFL_LOAD_FUNCTION(SamplerParameterIuivOES);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIivOES);
    GLFL_LOAD_FUNCTION(GetSamplerParameterIuivOES);
}
void glfl::load_extension_GL_OES_texture_buffer()
{
    GLFL_LOAD_FUNCTION(TexBufferOES);
    GLFL_LOAD_FUNCTION(TexBufferRangeOES);
}
void glfl::load_extension_GL_OES_texture_compression_astc() {}
void glfl::load_extension_GL_OES_texture_cube_map()
{
    GLFL_LOAD_FUNCTION(TexGenfOES);
    GLFL_LOAD_FUNCTION(TexGenfvOES);
    GLFL_LOAD_FUNCTION(TexGeniOES);
    GLFL_LOAD_FUNCTION(TexGenivOES);
    GLFL_LOAD_FUNCTION(TexGenxOES);
    GLFL_LOAD_FUNCTION(TexGenxvOES);
    GLFL_LOAD_FUNCTION(GetTexGenfvOES);
    GLFL_LOAD_FUNCTION(GetTexGenivOES);
    GLFL_LOAD_FUNCTION(GetTexGenxvOES);
}
void glfl::load_extension_GL_OES_texture_cube_map_array() {}
void glfl::load_extension_GL_OES_texture_env_crossbar() {}
void glfl::load_extension_GL_OES_texture_float() {}
void glfl::load_extension_GL_OES_texture_float_linear() {}
void glfl::load_extension_GL_OES_texture_half_float() {}
void glfl::load_extension_GL_OES_texture_half_float_linear() {}
void glfl::load_extension_GL_OES_texture_mirrored_repeat() {}
void glfl::load_extension_GL_OES_texture_npot() {}
void glfl::load_extension_GL_OES_texture_stencil8() {}
void glfl::load_extension_GL_OES_texture_storage_multisample_2d_array()
{
    GLFL_LOAD_FUNCTION(TexStorage3DMultisampleOES);
}
void glfl::load_extension_GL_OES_texture_view()
{
    GLFL_LOAD_FUNCTION(TextureViewOES);
}
void glfl::load_extension_GL_OES_vertex_array_object()
{
    GLFL_LOAD_FUNCTION(BindVertexArrayOES);
    GLFL_LOAD_FUNCTION(DeleteVertexArraysOES);
    GLFL_LOAD_FUNCTION(GenVertexArraysOES);
    GLFL_LOAD_FUNCTION(IsVertexArrayOES);
}
void glfl::load_extension_GL_OES_vertex_half_float() {}
void glfl::load_extension_GL_OES_vertex_type_10_10_10_2() {}
void glfl::load_extension_GL_OES_viewport_array()
{
    GLFL_LOAD_FUNCTION(ViewportArrayvOES);
    GLFL_LOAD_FUNCTION(ViewportIndexedfOES);
    GLFL_LOAD_FUNCTION(ViewportIndexedfvOES);
    GLFL_LOAD_FUNCTION(ScissorArrayvOES);
    GLFL_LOAD_FUNCTION(ScissorIndexedOES);
    GLFL_LOAD_FUNCTION(ScissorIndexedvOES);
    GLFL_LOAD_FUNCTION(DepthRangeArrayfvOES);
    GLFL_LOAD_FUNCTION(DepthRangeIndexedfOES);
    GLFL_LOAD_FUNCTION(GetFloati_vOES);
    GLFL_LOAD_FUNCTION(EnableiOES);
    GLFL_LOAD_FUNCTION(DisableiOES);
    GLFL_LOAD_FUNCTION(IsEnablediOES);
}
void glfl::load_extension_GL_OML_interlace() {}
void glfl::load_extension_GL_OML_resample() {}
void glfl::load_extension_GL_OML_subsample() {}
void glfl::load_extension_GL_OVR_multiview()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureMultiviewOVR);
}
void glfl::load_extension_GL_OVR_multiview2() {}
void glfl::load_extension_GL_OVR_multiview_multisampled_render_to_texture()
{
    GLFL_LOAD_FUNCTION(FramebufferTextureMultisampleMultiviewOVR);
}
void glfl::load_extension_GL_PGI_misc_hints()
{
    GLFL_LOAD_FUNCTION(HintPGI);
}
void glfl::load_extension_GL_PGI_vertex_hints() {}
void glfl::load_extension_GL_QCOM_alpha_test()
{
    GLFL_LOAD_FUNCTION(AlphaFuncQCOM);
}
void glfl::load_extension_GL_QCOM_binning_control() {}
void glfl::load_extension_GL_QCOM_driver_control()
{
    GLFL_LOAD_FUNCTION(GetDriverControlsQCOM);
    GLFL_LOAD_FUNCTION(GetDriverControlStringQCOM);
    GLFL_LOAD_FUNCTION(EnableDriverControlQCOM);
    GLFL_LOAD_FUNCTION(DisableDriverControlQCOM);
}
void glfl::load_extension_GL_QCOM_extended_get()
{
    GLFL_LOAD_FUNCTION(ExtGetTexturesQCOM);
    GLFL_LOAD_FUNCTION(ExtGetBuffersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetRenderbuffersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetFramebuffersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetTexLevelParameterivQCOM);
    GLFL_LOAD_FUNCTION(ExtTexObjectStateOverrideiQCOM);
    GLFL_LOAD_FUNCTION(ExtGetTexSubImageQCOM);
    GLFL_LOAD_FUNCTION(ExtGetBufferPointervQCOM);
}
void glfl::load_extension_GL_QCOM_extended_get2()
{
    GLFL_LOAD_FUNCTION(ExtGetShadersQCOM);
    GLFL_LOAD_FUNCTION(ExtGetProgramsQCOM);
    GLFL_LOAD_FUNCTION(ExtIsProgramBinaryQCOM);
    GLFL_LOAD_FUNCTION(ExtGetProgramBinarySourceQCOM);
}
void glfl::load_extension_GL_QCOM_perfmon_global_mode() {}
void glfl::load_extension_GL_QCOM_tiled_rendering()
{
    GLFL_LOAD_FUNCTION(StartTilingQCOM);
    GLFL_LOAD_FUNCTION(EndTilingQCOM);
}
void glfl::load_extension_GL_QCOM_writeonly_rendering() {}
void glfl::load_extension_GL_REND_screen_coordinates() {}
void glfl::load_extension_GL_S3_s3tc() {}
void glfl::load_extension_GL_SGIS_detail_texture()
{
    GLFL_LOAD_FUNCTION(DetailTexFuncSGIS);
    GLFL_LOAD_FUNCTION(GetDetailTexFuncSGIS);
}
void glfl::load_extension_GL_SGIS_fog_function()
{
    GLFL_LOAD_FUNCTION(FogFuncSGIS);
    GLFL_LOAD_FUNCTION(GetFogFuncSGIS);
}
void glfl::load_extension_GL_SGIS_generate_mipmap() {}
void glfl::load_extension_GL_SGIS_multisample()
{
    GLFL_LOAD_FUNCTION(SampleMaskSGIS);
    GLFL_LOAD_FUNCTION(SamplePatternSGIS);
}
void glfl::load_extension_GL_SGIS_pixel_texture()
{
    GLFL_LOAD_FUNCTION(PixelTexGenParameteriSGIS);
    GLFL_LOAD_FUNCTION(PixelTexGenParameterivSGIS);
    GLFL_LOAD_FUNCTION(PixelTexGenParameterfSGIS);
    GLFL_LOAD_FUNCTION(PixelTexGenParameterfvSGIS);
    GLFL_LOAD_FUNCTION(GetPixelTexGenParameterivSGIS);
    GLFL_LOAD_FUNCTION(GetPixelTexGenParameterfvSGIS);
}
void glfl::load_extension_GL_SGIS_point_line_texgen() {}
void glfl::load_extension_GL_SGIS_point_parameters()
{
    GLFL_LOAD_FUNCTION(PointParameterfSGIS);
    GLFL_LOAD_FUNCTION(PointParameterfvSGIS);
}
void glfl::load_extension_GL_SGIS_sharpen_texture()
{
    GLFL_LOAD_FUNCTION(SharpenTexFuncSGIS);
    GLFL_LOAD_FUNCTION(GetSharpenTexFuncSGIS);
}
void glfl::load_extension_GL_SGIS_texture4D()
{
    GLFL_LOAD_FUNCTION(TexImage4DSGIS);
    GLFL_LOAD_FUNCTION(TexSubImage4DSGIS);
}
void glfl::load_extension_GL_SGIS_texture_border_clamp() {}
void glfl::load_extension_GL_SGIS_texture_color_mask()
{
    GLFL_LOAD_FUNCTION(TextureColorMaskSGIS);
}
void glfl::load_extension_GL_SGIS_texture_edge_clamp() {}
void glfl::load_extension_GL_SGIS_texture_filter4()
{
    GLFL_LOAD_FUNCTION(GetTexFilterFuncSGIS);
    GLFL_LOAD_FUNCTION(TexFilterFuncSGIS);
}
void glfl::load_extension_GL_SGIS_texture_lod() {}
void glfl::load_extension_GL_SGIS_texture_select() {}
void glfl::load_extension_GL_SGIX_async()
{
    GLFL_LOAD_FUNCTION(AsyncMarkerSGIX);
    GLFL_LOAD_FUNCTION(FinishAsyncSGIX);
    GLFL_LOAD_FUNCTION(PollAsyncSGIX);
    GLFL_LOAD_FUNCTION(GenAsyncMarkersSGIX);
    GLFL_LOAD_FUNCTION(DeleteAsyncMarkersSGIX);
    GLFL_LOAD_FUNCTION(IsAsyncMarkerSGIX);
}
void glfl::load_extension_GL_SGIX_async_histogram() {}
void glfl::load_extension_GL_SGIX_async_pixel() {}
void glfl::load_extension_GL_SGIX_blend_alpha_minmax() {}
void glfl::load_extension_GL_SGIX_calligraphic_fragment() {}
void glfl::load_extension_GL_SGIX_clipmap() {}
void glfl::load_extension_GL_SGIX_convolution_accuracy() {}
void glfl::load_extension_GL_SGIX_depth_pass_instrument() {}
void glfl::load_extension_GL_SGIX_depth_texture() {}
void glfl::load_extension_GL_SGIX_flush_raster()
{
    GLFL_LOAD_FUNCTION(FlushRasterSGIX);
}
void glfl::load_extension_GL_SGIX_fog_offset() {}
void glfl::load_extension_GL_SGIX_fragment_lighting()
{
    GLFL_LOAD_FUNCTION(FragmentColorMaterialSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightfSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightfvSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightiSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightivSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModelfSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModelfvSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModeliSGIX);
    GLFL_LOAD_FUNCTION(FragmentLightModelivSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialfSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialfvSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialiSGIX);
    GLFL_LOAD_FUNCTION(FragmentMaterialivSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentLightfvSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentLightivSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentMaterialfvSGIX);
    GLFL_LOAD_FUNCTION(GetFragmentMaterialivSGIX);
    GLFL_LOAD_FUNCTION(LightEnviSGIX);
}
void glfl::load_extension_GL_SGIX_framezoom()
{
    GLFL_LOAD_FUNCTION(FrameZoomSGIX);
}
void glfl::load_extension_GL_SGIX_igloo_interface()
{
    GLFL_LOAD_FUNCTION(IglooInterfaceSGIX);
}
void glfl::load_extension_GL_SGIX_instruments()
{
    GLFL_LOAD_FUNCTION(GetInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(InstrumentsBufferSGIX);
    GLFL_LOAD_FUNCTION(PollInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(ReadInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(StartInstrumentsSGIX);
    GLFL_LOAD_FUNCTION(StopInstrumentsSGIX);
}
void glfl::load_extension_GL_SGIX_interlace() {}
void glfl::load_extension_GL_SGIX_ir_instrument1() {}
void glfl::load_extension_GL_SGIX_list_priority()
{
    GLFL_LOAD_FUNCTION(GetListParameterfvSGIX);
    GLFL_LOAD_FUNCTION(GetListParameterivSGIX);
    GLFL_LOAD_FUNCTION(ListParameterfSGIX);
    GLFL_LOAD_FUNCTION(ListParameterfvSGIX);
    GLFL_LOAD_FUNCTION(ListParameteriSGIX);
    GLFL_LOAD_FUNCTION(ListParameterivSGIX);
}
void glfl::load_extension_GL_SGIX_pixel_texture()
{
    GLFL_LOAD_FUNCTION(PixelTexGenSGIX);
}
void glfl::load_extension_GL_SGIX_pixel_tiles() {}
void glfl::load_extension_GL_SGIX_polynomial_ffd()
{
    GLFL_LOAD_FUNCTION(DeformationMap3dSGIX);
    GLFL_LOAD_FUNCTION(DeformationMap3fSGIX);
    GLFL_LOAD_FUNCTION(DeformSGIX);
    GLFL_LOAD_FUNCTION(LoadIdentityDeformationMapSGIX);
}
void glfl::load_extension_GL_SGIX_reference_plane()
{
    GLFL_LOAD_FUNCTION(ReferencePlaneSGIX);
}
void glfl::load_extension_GL_SGIX_resample() {}
void glfl::load_extension_GL_SGIX_scalebias_hint() {}
void glfl::load_extension_GL_SGIX_shadow() {}
void glfl::load_extension_GL_SGIX_shadow_ambient() {}
void glfl::load_extension_GL_SGIX_sprite()
{
    GLFL_LOAD_FUNCTION(SpriteParameterfSGIX);
    GLFL_LOAD_FUNCTION(SpriteParameterfvSGIX);
    GLFL_LOAD_FUNCTION(SpriteParameteriSGIX);
    GLFL_LOAD_FUNCTION(SpriteParameterivSGIX);
}
void glfl::load_extension_GL_SGIX_subsample() {}
void glfl::load_extension_GL_SGIX_tag_sample_buffer()
{
    GLFL_LOAD_FUNCTION(TagSampleBufferSGIX);
}
void glfl::load_extension_GL_SGIX_texture_add_env() {}
void glfl::load_extension_GL_SGIX_texture_coordinate_clamp() {}
void glfl::load_extension_GL_SGIX_texture_lod_bias() {}
void glfl::load_extension_GL_SGIX_texture_multi_buffer() {}
void glfl::load_extension_GL_SGIX_texture_scale_bias() {}
void glfl::load_extension_GL_SGIX_vertex_preclip() {}
void glfl::load_extension_GL_SGIX_ycrcb() {}
void glfl::load_extension_GL_SGIX_ycrcb_subsample() {}
void glfl::load_extension_GL_SGIX_ycrcba() {}
void glfl::load_extension_GL_SGI_color_matrix() {}
void glfl::load_extension_GL_SGI_color_table()
{
    GLFL_LOAD_FUNCTION(ColorTableSGI);
    GLFL_LOAD_FUNCTION(ColorTableParameterfvSGI);
    GLFL_LOAD_FUNCTION(ColorTableParameterivSGI);
    GLFL_LOAD_FUNCTION(CopyColorTableSGI);
    GLFL_LOAD_FUNCTION(GetColorTableSGI);
    GLFL_LOAD_FUNCTION(GetColorTableParameterfvSGI);
    GLFL_LOAD_FUNCTION(GetColorTableParameterivSGI);
}
void glfl::load_extension_GL_SGI_texture_color_table() {}
void glfl::load_extension_GL_SUNX_constant_data()
{
    GLFL_LOAD_FUNCTION(FinishTextureSUNX);
}
void glfl::load_extension_GL_SUN_convolution_border_modes() {}
void glfl::load_extension_GL_SUN_global_alpha()
{
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorbSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorsSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactoriSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorfSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactordSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorubSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactorusSUN);
    GLFL_LOAD_FUNCTION(GlobalAlphaFactoruiSUN);
}
void glfl::load_extension_GL_SUN_mesh_array()
{
    GLFL_LOAD_FUNCTION(DrawMeshArraysSUN);
}
void glfl::load_extension_GL_SUN_slice_accum() {}
void glfl::load_extension_GL_SUN_triangle_list()
{
    GLFL_LOAD_FUNCTION(ReplacementCodeuiSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeusSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeubSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuivSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeusvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeubvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodePointerSUN);
}
void glfl::load_extension_GL_SUN_vertex()
{
    GLFL_LOAD_FUNCTION(Color4ubVertex2fSUN);
    GLFL_LOAD_FUNCTION(Color4ubVertex2fvSUN);
    GLFL_LOAD_FUNCTION(Color4ubVertex3fSUN);
    GLFL_LOAD_FUNCTION(Color4ubVertex3fvSUN);
    GLFL_LOAD_FUNCTION(Color3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(Color3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(Normal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(Normal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(Color4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(Color4fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fVertex4fSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fVertex4fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4ubVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4ubVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(TexCoord2fColor4fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fColor4fNormal3fVertex4fSUN);
    GLFL_LOAD_FUNCTION(TexCoord4fColor4fNormal3fVertex4fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4ubVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4ubVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiColor4fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN);
    GLFL_LOAD_FUNCTION(ReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN);
}
void glfl::load_extension_GL_VIV_shader_binary() {}
void glfl::load_extension_GL_WIN_phong_shading() {}
void glfl::load_extension_GL_WIN_specular_fog() {}

const glfl::func_info &glfl::get_func_info(int index)
{
    static constexpr const char *pnames0[] {""};
    static constexpr const char *pnames1[] {"op", "value"};
    static constexpr const char *pnames2[] {"op", "value"};
    static constexpr const char *pnames3[] {"program"};
    static constexpr const char *pnames4[] {"pipeline", "program"};
    static constexpr const char *pnames5[] {"pipeline", "program"};
    static constexpr const char *pnames6[] {"face"};
    static constexpr const char *pnames7[] {"texture"};
    static constexpr const char *pnames8[] {"texture"};
    static constexpr const char *pnames9[] {"program", "name"};
    static constexpr const char *pnames10[] {"op", "dst", "dstMod", "arg1", "arg1Rep", "arg1Mod"};
    static constexpr const char *pnames11[] {"op", "dst", "dstMod", "arg1", "arg1Rep", "arg1Mod", "arg2", "arg2Rep", "arg2Mod"};
    static constexpr const char *pnames12[] {"op", "dst", "dstMod", "arg1", "arg1Rep", "arg1Mod", "arg2", "arg2Rep", "arg2Mod", "arg3", "arg3Rep", "arg3Mod"};
    static constexpr const char *pnames13[] {"func", "ref"};
    static constexpr const char *pnames14[] {"func", "ref"};
    static constexpr const char *pnames15[] {"func", "ref"};
    static constexpr const char *pnames16[] {"func", "ref"};
    static constexpr const char *pnames17[] {""};
    static constexpr const char *pnames18[] {"mode"};
    static constexpr const char *pnames19[] {"n", "programs", "residences"};
    static constexpr const char *pnames20[] {"n", "textures", "residences"};
    static constexpr const char *pnames21[] {"n", "textures", "residences"};
    static constexpr const char *pnames22[] {"i"};
    static constexpr const char *pnames23[] {"i"};
    static constexpr const char *pnames24[] {"array", "size", "type", "stride", "buffer", "offset"};
    static constexpr const char *pnames25[] {"marker"};
    static constexpr const char *pnames26[] {"containerObj", "obj"};
    static constexpr const char *pnames27[] {"program", "shader"};
    static constexpr const char *pnames28[] {"mode"};
    static constexpr const char *pnames29[] {"id", "mode"};
    static constexpr const char *pnames30[] {"id", "mode"};
    static constexpr const char *pnames31[] {"id"};
    static constexpr const char *pnames32[] {""};
    static constexpr const char *pnames33[] {"id"};
    static constexpr const char *pnames34[] {"monitor"};
    static constexpr const char *pnames35[] {"queryHandle"};
    static constexpr const char *pnames36[] {"target", "id"};
    static constexpr const char *pnames37[] {"target", "id"};
    static constexpr const char *pnames38[] {"target", "id"};
    static constexpr const char *pnames39[] {"target", "index", "id"};
    static constexpr const char *pnames40[] {"primitiveMode"};
    static constexpr const char *pnames41[] {"primitiveMode"};
    static constexpr const char *pnames42[] {"primitiveMode"};
    static constexpr const char *pnames43[] {""};
    static constexpr const char *pnames44[] {"video_capture_slot"};
    static constexpr const char *pnames45[] {"program", "index", "name"};
    static constexpr const char *pnames46[] {"programObj", "index", "name"};
    static constexpr const char *pnames47[] {"target", "buffer"};
    static constexpr const char *pnames48[] {"target", "buffer"};
    static constexpr const char *pnames49[] {"target", "index", "buffer"};
    static constexpr const char *pnames50[] {"target", "index", "buffer"};
    static constexpr const char *pnames51[] {"target", "index", "buffer"};
    static constexpr const char *pnames52[] {"target", "index", "buffer", "offset"};
    static constexpr const char *pnames53[] {"target", "index", "buffer", "offset"};
    static constexpr const char *pnames54[] {"target", "index", "buffer", "offset", "size"};
    static constexpr const char *pnames55[] {"target", "index", "buffer", "offset", "size"};
    static constexpr const char *pnames56[] {"target", "index", "buffer", "offset", "size"};
    static constexpr const char *pnames57[] {"target", "first", "count", "buffers"};
    static constexpr const char *pnames58[] {"target", "first", "count", "buffers", "offsets", "sizes"};
    static constexpr const char *pnames59[] {"program", "color", "name"};
    static constexpr const char *pnames60[] {"program", "color", "name"};
    static constexpr const char *pnames61[] {"program", "colorNumber", "index", "name"};
    static constexpr const char *pnames62[] {"program", "colorNumber", "index", "name"};
    static constexpr const char *pnames63[] {"id"};
    static constexpr const char *pnames64[] {"target", "framebuffer"};
    static constexpr const char *pnames65[] {"target", "framebuffer"};
    static constexpr const char *pnames66[] {"target", "framebuffer"};
    static constexpr const char *pnames67[] {"unit", "texture", "level", "layered", "layer", "access", "format"};
    static constexpr const char *pnames68[] {"index", "texture", "level", "layered", "layer", "access", "format"};
    static constexpr const char *pnames69[] {"first", "count", "textures"};
    static constexpr const char *pnames70[] {"light", "value"};
    static constexpr const char *pnames71[] {"face", "value"};
    static constexpr const char *pnames72[] {"texunit", "target", "texture"};
    static constexpr const char *pnames73[] {"value"};
    static constexpr const char *pnames74[] {"target", "program"};
    static constexpr const char *pnames75[] {"target", "id"};
    static constexpr const char *pnames76[] {"pipeline"};
    static constexpr const char *pnames77[] {"pipeline"};
    static constexpr const char *pnames78[] {"target", "renderbuffer"};
    static constexpr const char *pnames79[] {"target", "renderbuffer"};
    static constexpr const char *pnames80[] {"target", "renderbuffer"};
    static constexpr const char *pnames81[] {"unit", "sampler"};
    static constexpr const char *pnames82[] {"first", "count", "samplers"};
    static constexpr const char *pnames83[] {"unit", "coord", "value"};
    static constexpr const char *pnames84[] {"target", "texture"};
    static constexpr const char *pnames85[] {"target", "texture"};
    static constexpr const char *pnames86[] {"unit", "texture"};
    static constexpr const char *pnames87[] {"unit", "value"};
    static constexpr const char *pnames88[] {"first", "count", "textures"};
    static constexpr const char *pnames89[] {"target", "id"};
    static constexpr const char *pnames90[] {"target", "id"};
    static constexpr const char *pnames91[] {"array"};
    static constexpr const char *pnames92[] {"array"};
    static constexpr const char *pnames93[] {"array"};
    static constexpr const char *pnames94[] {"bindingindex", "buffer", "offset", "stride"};
    static constexpr const char *pnames95[] {"first", "count", "buffers", "offsets", "strides"};
    static constexpr const char *pnames96[] {"id"};
    static constexpr const char *pnames97[] {"video_capture_slot", "stream", "frame_region", "offset"};
    static constexpr const char *pnames98[] {"video_capture_slot", "stream", "frame_region", "target", "texture"};
    static constexpr const char *pnames99[] {"bx", "by", "bz"};
    static constexpr const char *pnames100[] {"v"};
    static constexpr const char *pnames101[] {"bx", "by", "bz"};
    static constexpr const char *pnames102[] {"v"};
    static constexpr const char *pnames103[] {"bx", "by", "bz"};
    static constexpr const char *pnames104[] {"v"};
    static constexpr const char *pnames105[] {"bx", "by", "bz"};
    static constexpr const char *pnames106[] {"v"};
    static constexpr const char *pnames107[] {"bx", "by", "bz"};
    static constexpr const char *pnames108[] {"v"};
    static constexpr const char *pnames109[] {"type", "stride", "pointer"};
    static constexpr const char *pnames110[] {"width", "height", "xorig", "yorig", "xmove", "ymove", "bitmap"};
    static constexpr const char *pnames111[] {"width", "height", "xorig", "yorig", "xmove", "ymove", "bitmap"};
    static constexpr const char *pnames112[] {""};
    static constexpr const char *pnames113[] {""};
    static constexpr const char *pnames114[] {""};
    static constexpr const char *pnames115[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames116[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames117[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames118[] {"mode"};
    static constexpr const char *pnames119[] {"mode"};
    static constexpr const char *pnames120[] {"buf", "mode"};
    static constexpr const char *pnames121[] {"mode"};
    static constexpr const char *pnames122[] {"modeRGB", "modeAlpha"};
    static constexpr const char *pnames123[] {"modeRGB", "modeAlpha"};
    static constexpr const char *pnames124[] {"buf", "modeRGB", "modeAlpha"};
    static constexpr const char *pnames125[] {"modeRGB", "modeAlpha"};
    static constexpr const char *pnames126[] {"buf", "modeRGB", "modeAlpha"};
    static constexpr const char *pnames127[] {"buf", "modeRGB", "modeAlpha"};
    static constexpr const char *pnames128[] {"buf", "modeRGB", "modeAlpha"};
    static constexpr const char *pnames129[] {"buf", "modeRGB", "modeAlpha"};
    static constexpr const char *pnames130[] {"buf", "mode"};
    static constexpr const char *pnames131[] {"buf", "mode"};
    static constexpr const char *pnames132[] {"buf", "mode"};
    static constexpr const char *pnames133[] {"buf", "mode"};
    static constexpr const char *pnames134[] {"sfactor", "dfactor"};
    static constexpr const char *pnames135[] {"buf", "src", "dst"};
    static constexpr const char *pnames136[] {"sfactorRGB", "dfactorRGB", "sfactorAlpha", "dfactorAlpha"};
    static constexpr const char *pnames137[] {"sfactorRGB", "dfactorRGB", "sfactorAlpha", "dfactorAlpha"};
    static constexpr const char *pnames138[] {"sfactorRGB", "dfactorRGB", "sfactorAlpha", "dfactorAlpha"};
    static constexpr const char *pnames139[] {"buf", "srcRGB", "dstRGB", "srcAlpha", "dstAlpha"};
    static constexpr const char *pnames140[] {"srcRGB", "dstRGB", "srcAlpha", "dstAlpha"};
    static constexpr const char *pnames141[] {"buf", "srcRGB", "dstRGB", "srcAlpha", "dstAlpha"};
    static constexpr const char *pnames142[] {"buf", "srcRGB", "dstRGB", "srcAlpha", "dstAlpha"};
    static constexpr const char *pnames143[] {"buf", "srcRGB", "dstRGB", "srcAlpha", "dstAlpha"};
    static constexpr const char *pnames144[] {"buf", "srcRGB", "dstRGB", "srcAlpha", "dstAlpha"};
    static constexpr const char *pnames145[] {"buf", "src", "dst"};
    static constexpr const char *pnames146[] {"buf", "src", "dst"};
    static constexpr const char *pnames147[] {"buf", "src", "dst"};
    static constexpr const char *pnames148[] {"buf", "src", "dst"};
    static constexpr const char *pnames149[] {"pname", "value"};
    static constexpr const char *pnames150[] {"srcX0", "srcY0", "srcX1", "srcY1", "dstX0", "dstY0", "dstX1", "dstY1", "mask", "filter"};
    static constexpr const char *pnames151[] {"srcX0", "srcY0", "srcX1", "srcY1", "dstX0", "dstY0", "dstX1", "dstY1", "mask", "filter"};
    static constexpr const char *pnames152[] {"srcX0", "srcY0", "srcX1", "srcY1", "dstX0", "dstY0", "dstX1", "dstY1", "mask", "filter"};
    static constexpr const char *pnames153[] {"srcX0", "srcY0", "srcX1", "srcY1", "dstX0", "dstY0", "dstX1", "dstY1", "mask", "filter"};
    static constexpr const char *pnames154[] {"readFramebuffer", "drawFramebuffer", "srcX0", "srcY0", "srcX1", "srcY1", "dstX0", "dstY0", "dstX1", "dstY1", "mask", "filter"};
    static constexpr const char *pnames155[] {"pname", "index", "address", "length"};
    static constexpr const char *pnames156[] {"target", "size", "data", "usage"};
    static constexpr const char *pnames157[] {"target", "size", "data", "usage"};
    static constexpr const char *pnames158[] {"target", "offset", "size", "commit"};
    static constexpr const char *pnames159[] {"target", "pname", "param"};
    static constexpr const char *pnames160[] {"target", "size", "data", "flags"};
    static constexpr const char *pnames161[] {"target", "size", "data", "flags"};
    static constexpr const char *pnames162[] {"target", "offset", "size", "data"};
    static constexpr const char *pnames163[] {"target", "offset", "size", "data"};
    static constexpr const char *pnames164[] {"list"};
    static constexpr const char *pnames165[] {"list"};
    static constexpr const char *pnames166[] {"n", "type", "lists"};
    static constexpr const char *pnames167[] {"target"};
    static constexpr const char *pnames168[] {"target"};
    static constexpr const char *pnames169[] {"target"};
    static constexpr const char *pnames170[] {"framebuffer", "target"};
    static constexpr const char *pnames171[] {"framebuffer", "target"};
    static constexpr const char *pnames172[] {"target", "clamp"};
    static constexpr const char *pnames173[] {"target", "clamp"};
    static constexpr const char *pnames174[] {"mask"};
    static constexpr const char *pnames175[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames176[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames177[] {"target", "internalformat", "format", "type", "data"};
    static constexpr const char *pnames178[] {"target", "internalformat", "offset", "size", "format", "type", "data"};
    static constexpr const char *pnames179[] {"buffer", "drawbuffer", "depth", "stencil"};
    static constexpr const char *pnames180[] {"buffer", "drawbuffer", "value"};
    static constexpr const char *pnames181[] {"buffer", "drawbuffer", "value"};
    static constexpr const char *pnames182[] {"buffer", "drawbuffer", "value"};
    static constexpr const char *pnames183[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames184[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames185[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames186[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames187[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames188[] {"depth"};
    static constexpr const char *pnames189[] {"depth"};
    static constexpr const char *pnames190[] {"d"};
    static constexpr const char *pnames191[] {"depth"};
    static constexpr const char *pnames192[] {"depth"};
    static constexpr const char *pnames193[] {"depth"};
    static constexpr const char *pnames194[] {"c"};
    static constexpr const char *pnames195[] {"buffer", "internalformat", "format", "type", "data"};
    static constexpr const char *pnames196[] {"buffer", "internalformat", "format", "type", "data"};
    static constexpr const char *pnames197[] {"buffer", "internalformat", "offset", "size", "format", "type", "data"};
    static constexpr const char *pnames198[] {"buffer", "internalformat", "offset", "size", "format", "type", "data"};
    static constexpr const char *pnames199[] {"framebuffer", "buffer", "drawbuffer", "depth", "stencil"};
    static constexpr const char *pnames200[] {"framebuffer", "buffer", "drawbuffer", "value"};
    static constexpr const char *pnames201[] {"framebuffer", "buffer", "drawbuffer", "value"};
    static constexpr const char *pnames202[] {"framebuffer", "buffer", "drawbuffer", "value"};
    static constexpr const char *pnames203[] {"offset", "n", "values"};
    static constexpr const char *pnames204[] {"s"};
    static constexpr const char *pnames205[] {"texture", "level", "format", "type", "data"};
    static constexpr const char *pnames206[] {"texture", "level", "format", "type", "data"};
    static constexpr const char *pnames207[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "data"};
    static constexpr const char *pnames208[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "data"};
    static constexpr const char *pnames209[] {"texture"};
    static constexpr const char *pnames210[] {"texture"};
    static constexpr const char *pnames211[] {"stream"};
    static constexpr const char *pnames212[] {"mask"};
    static constexpr const char *pnames213[] {"sync", "flags", "timeout"};
    static constexpr const char *pnames214[] {"sync", "flags", "timeout"};
    static constexpr const char *pnames215[] {"origin", "depth"};
    static constexpr const char *pnames216[] {"plane", "equation"};
    static constexpr const char *pnames217[] {"p", "eqn"};
    static constexpr const char *pnames218[] {"p", "eqn"};
    static constexpr const char *pnames219[] {"plane", "equation"};
    static constexpr const char *pnames220[] {"plane", "equation"};
    static constexpr const char *pnames221[] {"p", "eqn"};
    static constexpr const char *pnames222[] {"plane", "equation"};
    static constexpr const char *pnames223[] {"red", "green", "blue"};
    static constexpr const char *pnames224[] {"v"};
    static constexpr const char *pnames225[] {"red", "green", "blue"};
    static constexpr const char *pnames226[] {"v"};
    static constexpr const char *pnames227[] {"red", "green", "blue"};
    static constexpr const char *pnames228[] {"r", "g", "b", "x", "y", "z"};
    static constexpr const char *pnames229[] {"c", "v"};
    static constexpr const char *pnames230[] {"v"};
    static constexpr const char *pnames231[] {"red", "green", "blue"};
    static constexpr const char *pnames232[] {"v"};
    static constexpr const char *pnames233[] {"red", "green", "blue"};
    static constexpr const char *pnames234[] {"v"};
    static constexpr const char *pnames235[] {"red", "green", "blue"};
    static constexpr const char *pnames236[] {"v"};
    static constexpr const char *pnames237[] {"red", "green", "blue"};
    static constexpr const char *pnames238[] {"v"};
    static constexpr const char *pnames239[] {"red", "green", "blue"};
    static constexpr const char *pnames240[] {"v"};
    static constexpr const char *pnames241[] {"red", "green", "blue"};
    static constexpr const char *pnames242[] {"v"};
    static constexpr const char *pnames243[] {"red", "green", "blue"};
    static constexpr const char *pnames244[] {"components"};
    static constexpr const char *pnames245[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames246[] {"v"};
    static constexpr const char *pnames247[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames248[] {"v"};
    static constexpr const char *pnames249[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames250[] {"r", "g", "b", "a", "nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames251[] {"c", "n", "v"};
    static constexpr const char *pnames252[] {"v"};
    static constexpr const char *pnames253[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames254[] {"v"};
    static constexpr const char *pnames255[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames256[] {"v"};
    static constexpr const char *pnames257[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames258[] {"v"};
    static constexpr const char *pnames259[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames260[] {"r", "g", "b", "a", "x", "y"};
    static constexpr const char *pnames261[] {"c", "v"};
    static constexpr const char *pnames262[] {"r", "g", "b", "a", "x", "y", "z"};
    static constexpr const char *pnames263[] {"c", "v"};
    static constexpr const char *pnames264[] {"v"};
    static constexpr const char *pnames265[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames266[] {"v"};
    static constexpr const char *pnames267[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames268[] {"v"};
    static constexpr const char *pnames269[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames270[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames271[] {"components"};
    static constexpr const char *pnames272[] {"size", "type", "stride"};
    static constexpr const char *pnames273[] {"op", "dst", "dstMask", "dstMod", "arg1", "arg1Rep", "arg1Mod"};
    static constexpr const char *pnames274[] {"op", "dst", "dstMask", "dstMod", "arg1", "arg1Rep", "arg1Mod", "arg2", "arg2Rep", "arg2Mod"};
    static constexpr const char *pnames275[] {"op", "dst", "dstMask", "dstMod", "arg1", "arg1Rep", "arg1Mod", "arg2", "arg2Rep", "arg2Mod", "arg3", "arg3Rep", "arg3Mod"};
    static constexpr const char *pnames276[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames277[] {"index", "r", "g", "b", "a"};
    static constexpr const char *pnames278[] {"index", "r", "g", "b", "a"};
    static constexpr const char *pnames279[] {"index", "r", "g", "b", "a"};
    static constexpr const char *pnames280[] {"index", "r", "g", "b", "a"};
    static constexpr const char *pnames281[] {"face", "mode"};
    static constexpr const char *pnames282[] {"type", "color"};
    static constexpr const char *pnames283[] {"type", "color"};
    static constexpr const char *pnames284[] {"type", "color"};
    static constexpr const char *pnames285[] {"type", "color"};
    static constexpr const char *pnames286[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames287[] {"size", "type", "stride", "count", "pointer"};
    static constexpr const char *pnames288[] {"size", "type", "stride", "pointer", "ptrstride"};
    static constexpr const char *pnames289[] {"size", "type", "pointer"};
    static constexpr const char *pnames290[] {"target", "start", "count", "format", "type", "data"};
    static constexpr const char *pnames291[] {"target", "start", "count", "format", "type", "data"};
    static constexpr const char *pnames292[] {"target", "internalformat", "width", "format", "type", "table"};
    static constexpr const char *pnames293[] {"target", "internalFormat", "width", "format", "type", "table"};
    static constexpr const char *pnames294[] {"target", "pname", "params"};
    static constexpr const char *pnames295[] {"target", "pname", "params"};
    static constexpr const char *pnames296[] {"target", "pname", "params"};
    static constexpr const char *pnames297[] {"target", "pname", "params"};
    static constexpr const char *pnames298[] {"target", "internalformat", "width", "format", "type", "table"};
    static constexpr const char *pnames299[] {"stage", "portion", "variable", "input", "mapping", "componentUsage"};
    static constexpr const char *pnames300[] {"stage", "portion", "abOutput", "cdOutput", "sumOutput", "scale", "bias", "abDotProduct", "cdDotProduct", "muxSum"};
    static constexpr const char *pnames301[] {"pname", "param"};
    static constexpr const char *pnames302[] {"pname", "params"};
    static constexpr const char *pnames303[] {"pname", "param"};
    static constexpr const char *pnames304[] {"pname", "params"};
    static constexpr const char *pnames305[] {"stage", "pname", "params"};
    static constexpr const char *pnames306[] {"list", "segments"};
    static constexpr const char *pnames307[] {"list"};
    static constexpr const char *pnames308[] {"shader"};
    static constexpr const char *pnames309[] {"shaderObj"};
    static constexpr const char *pnames310[] {"shader", "count", "path", "length"};
    static constexpr const char *pnames311[] {"texunit", "target", "level", "internalformat", "width", "border", "imageSize", "bits"};
    static constexpr const char *pnames312[] {"texunit", "target", "level", "internalformat", "width", "height", "border", "imageSize", "bits"};
    static constexpr const char *pnames313[] {"texunit", "target", "level", "internalformat", "width", "height", "depth", "border", "imageSize", "bits"};
    static constexpr const char *pnames314[] {"texunit", "target", "level", "xoffset", "width", "format", "imageSize", "bits"};
    static constexpr const char *pnames315[] {"texunit", "target", "level", "xoffset", "yoffset", "width", "height", "format", "imageSize", "bits"};
    static constexpr const char *pnames316[] {"texunit", "target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "imageSize", "bits"};
    static constexpr const char *pnames317[] {"target", "level", "internalformat", "width", "border", "imageSize", "data"};
    static constexpr const char *pnames318[] {"target", "level", "internalformat", "width", "border", "imageSize", "data"};
    static constexpr const char *pnames319[] {"target", "level", "internalformat", "width", "height", "border", "imageSize", "data"};
    static constexpr const char *pnames320[] {"target", "level", "internalformat", "width", "height", "border", "imageSize", "data"};
    static constexpr const char *pnames321[] {"target", "level", "internalformat", "width", "height", "depth", "border", "imageSize", "data"};
    static constexpr const char *pnames322[] {"target", "level", "internalformat", "width", "height", "depth", "border", "imageSize", "data"};
    static constexpr const char *pnames323[] {"target", "level", "internalformat", "width", "height", "depth", "border", "imageSize", "data"};
    static constexpr const char *pnames324[] {"target", "level", "xoffset", "width", "format", "imageSize", "data"};
    static constexpr const char *pnames325[] {"target", "level", "xoffset", "width", "format", "imageSize", "data"};
    static constexpr const char *pnames326[] {"target", "level", "xoffset", "yoffset", "width", "height", "format", "imageSize", "data"};
    static constexpr const char *pnames327[] {"target", "level", "xoffset", "yoffset", "width", "height", "format", "imageSize", "data"};
    static constexpr const char *pnames328[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "imageSize", "data"};
    static constexpr const char *pnames329[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "imageSize", "data"};
    static constexpr const char *pnames330[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "imageSize", "data"};
    static constexpr const char *pnames331[] {"texture", "target", "level", "internalformat", "width", "border", "imageSize", "bits"};
    static constexpr const char *pnames332[] {"texture", "target", "level", "internalformat", "width", "height", "border", "imageSize", "bits"};
    static constexpr const char *pnames333[] {"texture", "target", "level", "internalformat", "width", "height", "depth", "border", "imageSize", "bits"};
    static constexpr const char *pnames334[] {"texture", "level", "xoffset", "width", "format", "imageSize", "data"};
    static constexpr const char *pnames335[] {"texture", "target", "level", "xoffset", "width", "format", "imageSize", "bits"};
    static constexpr const char *pnames336[] {"texture", "level", "xoffset", "yoffset", "width", "height", "format", "imageSize", "data"};
    static constexpr const char *pnames337[] {"texture", "target", "level", "xoffset", "yoffset", "width", "height", "format", "imageSize", "bits"};
    static constexpr const char *pnames338[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "imageSize", "data"};
    static constexpr const char *pnames339[] {"texture", "target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "imageSize", "bits"};
    static constexpr const char *pnames340[] {"pname", "value"};
    static constexpr const char *pnames341[] {"pname", "param"};
    static constexpr const char *pnames342[] {"target", "internalformat", "width", "format", "type", "image"};
    static constexpr const char *pnames343[] {"target", "internalformat", "width", "format", "type", "image"};
    static constexpr const char *pnames344[] {"target", "internalformat", "width", "height", "format", "type", "image"};
    static constexpr const char *pnames345[] {"target", "internalformat", "width", "height", "format", "type", "image"};
    static constexpr const char *pnames346[] {"target", "pname", "params"};
    static constexpr const char *pnames347[] {"target", "pname", "params"};
    static constexpr const char *pnames348[] {"target", "pname", "params"};
    static constexpr const char *pnames349[] {"target", "pname", "params"};
    static constexpr const char *pnames350[] {"target", "pname", "params"};
    static constexpr const char *pnames351[] {"target", "pname", "params"};
    static constexpr const char *pnames352[] {"target", "pname", "params"};
    static constexpr const char *pnames353[] {"target", "pname", "params"};
    static constexpr const char *pnames354[] {"target", "pname", "param"};
    static constexpr const char *pnames355[] {"target", "pname", "params"};
    static constexpr const char *pnames356[] {"readTarget", "writeTarget", "readOffset", "writeOffset", "size"};
    static constexpr const char *pnames357[] {"readTarget", "writeTarget", "readOffset", "writeOffset", "size"};
    static constexpr const char *pnames358[] {"target", "start", "x", "y", "width"};
    static constexpr const char *pnames359[] {"target", "start", "x", "y", "width"};
    static constexpr const char *pnames360[] {"target", "internalformat", "x", "y", "width"};
    static constexpr const char *pnames361[] {"target", "internalformat", "x", "y", "width"};
    static constexpr const char *pnames362[] {"target", "internalformat", "x", "y", "width"};
    static constexpr const char *pnames363[] {"target", "internalformat", "x", "y", "width"};
    static constexpr const char *pnames364[] {"target", "internalformat", "x", "y", "width", "height"};
    static constexpr const char *pnames365[] {"target", "internalformat", "x", "y", "width", "height"};
    static constexpr const char *pnames366[] {"srcName", "srcTarget", "srcLevel", "srcX", "srcY", "srcZ", "dstName", "dstTarget", "dstLevel", "dstX", "dstY", "dstZ", "srcWidth", "srcHeight", "srcDepth"};
    static constexpr const char *pnames367[] {"srcName", "srcTarget", "srcLevel", "srcX", "srcY", "srcZ", "dstName", "dstTarget", "dstLevel", "dstX", "dstY", "dstZ", "srcWidth", "srcHeight", "srcDepth"};
    static constexpr const char *pnames368[] {"srcName", "srcTarget", "srcLevel", "srcX", "srcY", "srcZ", "dstName", "dstTarget", "dstLevel", "dstX", "dstY", "dstZ", "width", "height", "depth"};
    static constexpr const char *pnames369[] {"srcName", "srcTarget", "srcLevel", "srcX", "srcY", "srcZ", "dstName", "dstTarget", "dstLevel", "dstX", "dstY", "dstZ", "srcWidth", "srcHeight", "srcDepth"};
    static constexpr const char *pnames370[] {"texunit", "target", "level", "internalformat", "x", "y", "width", "border"};
    static constexpr const char *pnames371[] {"texunit", "target", "level", "internalformat", "x", "y", "width", "height", "border"};
    static constexpr const char *pnames372[] {"texunit", "target", "level", "xoffset", "x", "y", "width"};
    static constexpr const char *pnames373[] {"texunit", "target", "level", "xoffset", "yoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames374[] {"texunit", "target", "level", "xoffset", "yoffset", "zoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames375[] {"readBuffer", "writeBuffer", "readOffset", "writeOffset", "size"};
    static constexpr const char *pnames376[] {"resultPath", "srcPath"};
    static constexpr const char *pnames377[] {"x", "y", "width", "height", "type"};
    static constexpr const char *pnames378[] {"target", "level", "internalformat", "x", "y", "width", "border"};
    static constexpr const char *pnames379[] {"target", "level", "internalformat", "x", "y", "width", "border"};
    static constexpr const char *pnames380[] {"target", "level", "internalformat", "x", "y", "width", "height", "border"};
    static constexpr const char *pnames381[] {"target", "level", "internalformat", "x", "y", "width", "height", "border"};
    static constexpr const char *pnames382[] {"target", "level", "xoffset", "x", "y", "width"};
    static constexpr const char *pnames383[] {"target", "level", "xoffset", "x", "y", "width"};
    static constexpr const char *pnames384[] {"target", "level", "xoffset", "yoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames385[] {"target", "level", "xoffset", "yoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames386[] {"target", "level", "xoffset", "yoffset", "zoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames387[] {"target", "level", "xoffset", "yoffset", "zoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames388[] {"target", "level", "xoffset", "yoffset", "zoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames389[] {"texture", "target", "level", "internalformat", "x", "y", "width", "border"};
    static constexpr const char *pnames390[] {"texture", "target", "level", "internalformat", "x", "y", "width", "height", "border"};
    static constexpr const char *pnames391[] {"destinationTexture", "sourceTexture", "sourceBaseLevel", "sourceLevelCount"};
    static constexpr const char *pnames392[] {"texture", "level", "xoffset", "x", "y", "width"};
    static constexpr const char *pnames393[] {"texture", "target", "level", "xoffset", "x", "y", "width"};
    static constexpr const char *pnames394[] {"texture", "level", "xoffset", "yoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames395[] {"texture", "target", "level", "xoffset", "yoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames396[] {"texture", "level", "xoffset", "yoffset", "zoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames397[] {"texture", "target", "level", "xoffset", "yoffset", "zoffset", "x", "y", "width", "height"};
    static constexpr const char *pnames398[] {"numPaths", "pathNameType", "paths", "pathBase", "coverMode", "transformType", "transformValues"};
    static constexpr const char *pnames399[] {"path", "coverMode"};
    static constexpr const char *pnames400[] {"numPaths", "pathNameType", "paths", "pathBase", "coverMode", "transformType", "transformValues"};
    static constexpr const char *pnames401[] {"path", "coverMode"};
    static constexpr const char *pnames402[] {"mask"};
    static constexpr const char *pnames403[] {"components"};
    static constexpr const char *pnames404[] {"n", "v"};
    static constexpr const char *pnames405[] {"operation"};
    static constexpr const char *pnames406[] {"n", "buffers"};
    static constexpr const char *pnames407[] {"n", "lists"};
    static constexpr const char *pnames408[] {"n", "framebuffers"};
    static constexpr const char *pnames409[] {"queryId", "queryHandle"};
    static constexpr const char *pnames410[] {""};
    static constexpr const char *pnames411[] {""};
    static constexpr const char *pnames412[] {"n", "pipelines"};
    static constexpr const char *pnames413[] {"target", "n", "ids"};
    static constexpr const char *pnames414[] {"n", "renderbuffers"};
    static constexpr const char *pnames415[] {"n", "samplers"};
    static constexpr const char *pnames416[] {"type"};
    static constexpr const char *pnames417[] {"shaderType"};
    static constexpr const char *pnames418[] {"type", "string"};
    static constexpr const char *pnames419[] {"type", "count", "strings"};
    static constexpr const char *pnames420[] {"type", "count", "strings"};
    static constexpr const char *pnames421[] {"n", "states"};
    static constexpr const char *pnames422[] {"context", "event", "flags"};
    static constexpr const char *pnames423[] {"target", "n", "textures"};
    static constexpr const char *pnames424[] {"n", "ids"};
    static constexpr const char *pnames425[] {"n", "arrays"};
    static constexpr const char *pnames426[] {"mode"};
    static constexpr const char *pnames427[] {"pname", "params"};
    static constexpr const char *pnames428[] {"pname", "params"};
    static constexpr const char *pnames429[] {"index"};
    static constexpr const char *pnames430[] {"matrixpaletteindex"};
    static constexpr const char *pnames431[] {"callback", "userParam"};
    static constexpr const char *pnames432[] {"callback", "userParam"};
    static constexpr const char *pnames433[] {"callback", "userParam"};
    static constexpr const char *pnames434[] {"callback", "userParam"};
    static constexpr const char *pnames435[] {"source", "type", "severity", "count", "ids", "enabled"};
    static constexpr const char *pnames436[] {"source", "type", "severity", "count", "ids", "enabled"};
    static constexpr const char *pnames437[] {"source", "type", "severity", "count", "ids", "enabled"};
    static constexpr const char *pnames438[] {"category", "severity", "count", "ids", "enabled"};
    static constexpr const char *pnames439[] {"source", "type", "id", "severity", "length", "buf"};
    static constexpr const char *pnames440[] {"category", "severity", "id", "length", "buf"};
    static constexpr const char *pnames441[] {"source", "type", "id", "severity", "length", "buf"};
    static constexpr const char *pnames442[] {"source", "type", "id", "severity", "length", "buf"};
    static constexpr const char *pnames443[] {"mask"};
    static constexpr const char *pnames444[] {"target", "u1", "u2", "ustride", "uorder", "v1", "v2", "vstride", "vorder", "w1", "w2", "wstride", "worder", "points"};
    static constexpr const char *pnames445[] {"target", "u1", "u2", "ustride", "uorder", "v1", "v2", "vstride", "vorder", "w1", "w2", "wstride", "worder", "points"};
    static constexpr const char *pnames446[] {"marker", "range"};
    static constexpr const char *pnames447[] {"n", "buffers"};
    static constexpr const char *pnames448[] {"n", "buffers"};
    static constexpr const char *pnames449[] {"n", "lists"};
    static constexpr const char *pnames450[] {"n", "fences"};
    static constexpr const char *pnames451[] {"n", "fences"};
    static constexpr const char *pnames452[] {"id"};
    static constexpr const char *pnames453[] {"n", "framebuffers"};
    static constexpr const char *pnames454[] {"n", "framebuffers"};
    static constexpr const char *pnames455[] {"n", "framebuffers"};
    static constexpr const char *pnames456[] {"list", "range"};
    static constexpr const char *pnames457[] {"namelen", "name"};
    static constexpr const char *pnames458[] {"identifier", "num", "names"};
    static constexpr const char *pnames459[] {"obj"};
    static constexpr const char *pnames460[] {"n", "ids"};
    static constexpr const char *pnames461[] {"path", "range"};
    static constexpr const char *pnames462[] {"n", "monitors"};
    static constexpr const char *pnames463[] {"queryHandle"};
    static constexpr const char *pnames464[] {"program"};
    static constexpr const char *pnames465[] {"n", "pipelines"};
    static constexpr const char *pnames466[] {"n", "pipelines"};
    static constexpr const char *pnames467[] {"n", "programs"};
    static constexpr const char *pnames468[] {"n", "programs"};
    static constexpr const char *pnames469[] {"n", "ids"};
    static constexpr const char *pnames470[] {"n", "ids"};
    static constexpr const char *pnames471[] {"n", "ids"};
    static constexpr const char *pnames472[] {"n", "renderbuffers"};
    static constexpr const char *pnames473[] {"n", "renderbuffers"};
    static constexpr const char *pnames474[] {"n", "renderbuffers"};
    static constexpr const char *pnames475[] {"count", "samplers"};
    static constexpr const char *pnames476[] {"shader"};
    static constexpr const char *pnames477[] {"n", "states"};
    static constexpr const char *pnames478[] {"sync"};
    static constexpr const char *pnames479[] {"sync"};
    static constexpr const char *pnames480[] {"n", "textures"};
    static constexpr const char *pnames481[] {"n", "textures"};
    static constexpr const char *pnames482[] {"n", "ids"};
    static constexpr const char *pnames483[] {"n", "ids"};
    static constexpr const char *pnames484[] {"n", "arrays"};
    static constexpr const char *pnames485[] {"n", "arrays"};
    static constexpr const char *pnames486[] {"n", "arrays"};
    static constexpr const char *pnames487[] {"id"};
    static constexpr const char *pnames488[] {"zmin", "zmax"};
    static constexpr const char *pnames489[] {"zmin", "zmax"};
    static constexpr const char *pnames490[] {"func"};
    static constexpr const char *pnames491[] {"flag"};
    static constexpr const char *pnames492[] {"near", "far"};
    static constexpr const char *pnames493[] {"first", "count", "v"};
    static constexpr const char *pnames494[] {"first", "count", "v"};
    static constexpr const char *pnames495[] {"first", "count", "v"};
    static constexpr const char *pnames496[] {"index", "n", "f"};
    static constexpr const char *pnames497[] {"index", "n", "f"};
    static constexpr const char *pnames498[] {"index", "n", "f"};
    static constexpr const char *pnames499[] {"zNear", "zFar"};
    static constexpr const char *pnames500[] {"n", "f"};
    static constexpr const char *pnames501[] {"n", "f"};
    static constexpr const char *pnames502[] {"n", "f"};
    static constexpr const char *pnames503[] {"n", "f"};
    static constexpr const char *pnames504[] {"containerObj", "attachedObj"};
    static constexpr const char *pnames505[] {"program", "shader"};
    static constexpr const char *pnames506[] {"target", "n", "points"};
    static constexpr const char *pnames507[] {"cap"};
    static constexpr const char *pnames508[] {"array"};
    static constexpr const char *pnames509[] {"array", "index"};
    static constexpr const char *pnames510[] {"array", "index"};
    static constexpr const char *pnames511[] {"driverControl"};
    static constexpr const char *pnames512[] {"target", "index"};
    static constexpr const char *pnames513[] {"id"};
    static constexpr const char *pnames514[] {"vaobj", "index"};
    static constexpr const char *pnames515[] {"vaobj", "index"};
    static constexpr const char *pnames516[] {"vaobj", "array"};
    static constexpr const char *pnames517[] {"index", "pname"};
    static constexpr const char *pnames518[] {"index"};
    static constexpr const char *pnames519[] {"index"};
    static constexpr const char *pnames520[] {"target", "index"};
    static constexpr const char *pnames521[] {"target", "index"};
    static constexpr const char *pnames522[] {"target", "index"};
    static constexpr const char *pnames523[] {"target", "index"};
    static constexpr const char *pnames524[] {"target", "numAttachments", "attachments"};
    static constexpr const char *pnames525[] {"num_groups_x", "num_groups_y", "num_groups_z"};
    static constexpr const char *pnames526[] {"num_groups_x", "num_groups_y", "num_groups_z", "group_size_x", "group_size_y", "group_size_z"};
    static constexpr const char *pnames527[] {"indirect"};
    static constexpr const char *pnames528[] {"mode", "first", "count"};
    static constexpr const char *pnames529[] {"mode", "first", "count"};
    static constexpr const char *pnames530[] {"mode", "indirect"};
    static constexpr const char *pnames531[] {"mode", "first", "count", "instancecount"};
    static constexpr const char *pnames532[] {"mode", "first", "count", "primcount"};
    static constexpr const char *pnames533[] {"mode", "first", "count", "primcount"};
    static constexpr const char *pnames534[] {"mode", "first", "count", "instancecount", "baseinstance"};
    static constexpr const char *pnames535[] {"mode", "first", "count", "instancecount", "baseinstance"};
    static constexpr const char *pnames536[] {"mode", "start", "count", "primcount"};
    static constexpr const char *pnames537[] {"mode", "first", "count", "primcount"};
    static constexpr const char *pnames538[] {"buf"};
    static constexpr const char *pnames539[] {"n", "bufs"};
    static constexpr const char *pnames540[] {"n", "bufs"};
    static constexpr const char *pnames541[] {"n", "bufs"};
    static constexpr const char *pnames542[] {"n", "bufs"};
    static constexpr const char *pnames543[] {"n", "location", "indices"};
    static constexpr const char *pnames544[] {"n", "bufs"};
    static constexpr const char *pnames545[] {"primitiveMode", "indirects", "sizes", "count"};
    static constexpr const char *pnames546[] {"primitiveMode", "buffer", "indirects", "sizes", "count"};
    static constexpr const char *pnames547[] {"indirects", "sizes", "states", "fbos", "count"};
    static constexpr const char *pnames548[] {"buffer", "indirects", "sizes", "states", "fbos", "count"};
    static constexpr const char *pnames549[] {"mode", "first", "count"};
    static constexpr const char *pnames550[] {"mode", "count"};
    static constexpr const char *pnames551[] {"mode", "count", "type", "indices"};
    static constexpr const char *pnames552[] {"mode", "count", "type", "indices", "basevertex"};
    static constexpr const char *pnames553[] {"mode", "count", "type", "indices", "basevertex"};
    static constexpr const char *pnames554[] {"mode", "count", "type", "indices", "basevertex"};
    static constexpr const char *pnames555[] {"mode", "type", "indirect"};
    static constexpr const char *pnames556[] {"mode", "count", "type", "indices", "instancecount"};
    static constexpr const char *pnames557[] {"mode", "count", "type", "indices", "primcount"};
    static constexpr const char *pnames558[] {"mode", "count", "type", "indices", "primcount"};
    static constexpr const char *pnames559[] {"mode", "count", "type", "indices", "instancecount", "baseinstance"};
    static constexpr const char *pnames560[] {"mode", "count", "type", "indices", "instancecount", "baseinstance"};
    static constexpr const char *pnames561[] {"mode", "count", "type", "indices", "instancecount", "basevertex"};
    static constexpr const char *pnames562[] {"mode", "count", "type", "indices", "instancecount", "basevertex", "baseinstance"};
    static constexpr const char *pnames563[] {"mode", "count", "type", "indices", "instancecount", "basevertex", "baseinstance"};
    static constexpr const char *pnames564[] {"mode", "count", "type", "indices", "instancecount", "basevertex"};
    static constexpr const char *pnames565[] {"mode", "count", "type", "indices", "instancecount", "basevertex"};
    static constexpr const char *pnames566[] {"mode", "count", "type", "indices", "primcount"};
    static constexpr const char *pnames567[] {"mode", "count", "type", "indices", "primcount"};
    static constexpr const char *pnames568[] {"mode", "first", "count", "width"};
    static constexpr const char *pnames569[] {"width", "height", "format", "type", "pixels"};
    static constexpr const char *pnames570[] {"mode", "start", "end", "first", "count"};
    static constexpr const char *pnames571[] {"mode", "start", "end", "count"};
    static constexpr const char *pnames572[] {"mode", "start", "end", "count", "type", "indices"};
    static constexpr const char *pnames573[] {"mode", "start", "end", "count", "type", "indices", "basevertex"};
    static constexpr const char *pnames574[] {"mode", "start", "end", "count", "type", "indices", "basevertex"};
    static constexpr const char *pnames575[] {"mode", "start", "end", "count", "type", "indices", "basevertex"};
    static constexpr const char *pnames576[] {"mode", "start", "end", "count", "type", "indices"};
    static constexpr const char *pnames577[] {"x", "y", "z", "width", "height"};
    static constexpr const char *pnames578[] {"coords"};
    static constexpr const char *pnames579[] {"x", "y", "z", "width", "height"};
    static constexpr const char *pnames580[] {"coords"};
    static constexpr const char *pnames581[] {"x", "y", "z", "width", "height"};
    static constexpr const char *pnames582[] {"coords"};
    static constexpr const char *pnames583[] {"texture", "sampler", "x0", "y0", "x1", "y1", "z", "s0", "t0", "s1", "t1"};
    static constexpr const char *pnames584[] {"x", "y", "z", "width", "height"};
    static constexpr const char *pnames585[] {"coords"};
    static constexpr const char *pnames586[] {"mode", "id"};
    static constexpr const char *pnames587[] {"mode", "id"};
    static constexpr const char *pnames588[] {"mode", "id", "instancecount"};
    static constexpr const char *pnames589[] {"mode", "id", "instancecount"};
    static constexpr const char *pnames590[] {"mode", "id"};
    static constexpr const char *pnames591[] {"mode", "id", "stream"};
    static constexpr const char *pnames592[] {"mode", "id", "stream", "instancecount"};
    static constexpr const char *pnames593[] {"target", "image"};
    static constexpr const char *pnames594[] {"target", "image"};
    static constexpr const char *pnames595[] {"flag"};
    static constexpr const char *pnames596[] {"stride"};
    static constexpr const char *pnames597[] {"stride", "pointer"};
    static constexpr const char *pnames598[] {"stride", "count", "pointer"};
    static constexpr const char *pnames599[] {"stride", "pointer", "ptrstride"};
    static constexpr const char *pnames600[] {"flag"};
    static constexpr const char *pnames601[] {"type", "pointer"};
    static constexpr const char *pnames602[] {"type", "pointer"};
    static constexpr const char *pnames603[] {"cap"};
    static constexpr const char *pnames604[] {"array"};
    static constexpr const char *pnames605[] {"array", "index"};
    static constexpr const char *pnames606[] {"array", "index"};
    static constexpr const char *pnames607[] {"driverControl"};
    static constexpr const char *pnames608[] {"target", "index"};
    static constexpr const char *pnames609[] {"id"};
    static constexpr const char *pnames610[] {"vaobj", "index"};
    static constexpr const char *pnames611[] {"vaobj", "index"};
    static constexpr const char *pnames612[] {"vaobj", "array"};
    static constexpr const char *pnames613[] {"index", "pname"};
    static constexpr const char *pnames614[] {"index"};
    static constexpr const char *pnames615[] {"index"};
    static constexpr const char *pnames616[] {"target", "index"};
    static constexpr const char *pnames617[] {"target", "index"};
    static constexpr const char *pnames618[] {"target", "index"};
    static constexpr const char *pnames619[] {"target", "index"};
    static constexpr const char *pnames620[] {""};
    static constexpr const char *pnames621[] {""};
    static constexpr const char *pnames622[] {""};
    static constexpr const char *pnames623[] {""};
    static constexpr const char *pnames624[] {""};
    static constexpr const char *pnames625[] {""};
    static constexpr const char *pnames626[] {""};
    static constexpr const char *pnames627[] {"monitor"};
    static constexpr const char *pnames628[] {"queryHandle"};
    static constexpr const char *pnames629[] {"target"};
    static constexpr const char *pnames630[] {"target"};
    static constexpr const char *pnames631[] {"target"};
    static constexpr const char *pnames632[] {"target", "index"};
    static constexpr const char *pnames633[] {"preserveMask"};
    static constexpr const char *pnames634[] {""};
    static constexpr const char *pnames635[] {""};
    static constexpr const char *pnames636[] {""};
    static constexpr const char *pnames637[] {""};
    static constexpr const char *pnames638[] {"video_capture_slot"};
    static constexpr const char *pnames639[] {"u"};
    static constexpr const char *pnames640[] {"u"};
    static constexpr const char *pnames641[] {"u"};
    static constexpr const char *pnames642[] {"u"};
    static constexpr const char *pnames643[] {"u"};
    static constexpr const char *pnames644[] {"coords"};
    static constexpr const char *pnames645[] {"u", "v"};
    static constexpr const char *pnames646[] {"u"};
    static constexpr const char *pnames647[] {"u", "v"};
    static constexpr const char *pnames648[] {"u"};
    static constexpr const char *pnames649[] {"u", "v"};
    static constexpr const char *pnames650[] {"coords"};
    static constexpr const char *pnames651[] {"target", "mode"};
    static constexpr const char *pnames652[] {"mode", "i1", "i2"};
    static constexpr const char *pnames653[] {"mode", "i1", "i2", "j1", "j2"};
    static constexpr const char *pnames654[] {"i"};
    static constexpr const char *pnames655[] {"i", "j"};
    static constexpr const char *pnames656[] {""};
    static constexpr const char *pnames657[] {"target", "id", "params"};
    static constexpr const char *pnames658[] {"target", "params"};
    static constexpr const char *pnames659[] {"buffers", "maxBuffers", "numBuffers"};
    static constexpr const char *pnames660[] {"framebuffers", "maxFramebuffers", "numFramebuffers"};
    static constexpr const char *pnames661[] {"program", "shadertype", "source", "length"};
    static constexpr const char *pnames662[] {"programs", "maxPrograms", "numPrograms"};
    static constexpr const char *pnames663[] {"renderbuffers", "maxRenderbuffers", "numRenderbuffers"};
    static constexpr const char *pnames664[] {"shaders", "maxShaders", "numShaders"};
    static constexpr const char *pnames665[] {"texture", "face", "level", "pname", "params"};
    static constexpr const char *pnames666[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "texels"};
    static constexpr const char *pnames667[] {"textures", "maxTextures", "numTextures"};
    static constexpr const char *pnames668[] {"program"};
    static constexpr const char *pnames669[] {"target", "pname", "param"};
    static constexpr const char *pnames670[] {"res", "src", "num"};
    static constexpr const char *pnames671[] {"size", "type", "buffer"};
    static constexpr const char *pnames672[] {"n", "type", "buffer"};
    static constexpr const char *pnames673[] {"condition", "flags"};
    static constexpr const char *pnames674[] {"condition", "flags"};
    static constexpr const char *pnames675[] {"variable", "input", "mapping", "componentUsage"};
    static constexpr const char *pnames676[] {""};
    static constexpr const char *pnames677[] {"markerp"};
    static constexpr const char *pnames678[] {"fence"};
    static constexpr const char *pnames679[] {"fence"};
    static constexpr const char *pnames680[] {"object", "name"};
    static constexpr const char *pnames681[] {""};
    static constexpr const char *pnames682[] {""};
    static constexpr const char *pnames683[] {"target", "offset", "length"};
    static constexpr const char *pnames684[] {"target", "offset", "size"};
    static constexpr const char *pnames685[] {"target", "offset", "length"};
    static constexpr const char *pnames686[] {"buffer", "offset", "length"};
    static constexpr const char *pnames687[] {"buffer", "offset", "length"};
    static constexpr const char *pnames688[] {"target"};
    static constexpr const char *pnames689[] {""};
    static constexpr const char *pnames690[] {"target"};
    static constexpr const char *pnames691[] {"length", "pointer"};
    static constexpr const char *pnames692[] {""};
    static constexpr const char *pnames693[] {"type", "stride"};
    static constexpr const char *pnames694[] {"type", "stride", "pointer"};
    static constexpr const char *pnames695[] {"type", "stride", "pointer"};
    static constexpr const char *pnames696[] {"type", "stride", "pointer", "ptrstride"};
    static constexpr const char *pnames697[] {"coord"};
    static constexpr const char *pnames698[] {"coord"};
    static constexpr const char *pnames699[] {"coord"};
    static constexpr const char *pnames700[] {"coord"};
    static constexpr const char *pnames701[] {"coord"};
    static constexpr const char *pnames702[] {"coord"};
    static constexpr const char *pnames703[] {"coord"};
    static constexpr const char *pnames704[] {"coord"};
    static constexpr const char *pnames705[] {"fog"};
    static constexpr const char *pnames706[] {"fog"};
    static constexpr const char *pnames707[] {"n", "points"};
    static constexpr const char *pnames708[] {"pname", "param"};
    static constexpr const char *pnames709[] {"pname", "params"};
    static constexpr const char *pnames710[] {"pname", "param"};
    static constexpr const char *pnames711[] {"pname", "params"};
    static constexpr const char *pnames712[] {"pname", "param"};
    static constexpr const char *pnames713[] {"pname", "param"};
    static constexpr const char *pnames714[] {"pname", "param"};
    static constexpr const char *pnames715[] {"pname", "param"};
    static constexpr const char *pnames716[] {"face", "mode"};
    static constexpr const char *pnames717[] {"color"};
    static constexpr const char *pnames718[] {"pname", "param"};
    static constexpr const char *pnames719[] {"pname", "params"};
    static constexpr const char *pnames720[] {"pname", "param"};
    static constexpr const char *pnames721[] {"pname", "params"};
    static constexpr const char *pnames722[] {"light", "pname", "param"};
    static constexpr const char *pnames723[] {"light", "pname", "params"};
    static constexpr const char *pnames724[] {"light", "pname", "param"};
    static constexpr const char *pnames725[] {"light", "pname", "params"};
    static constexpr const char *pnames726[] {"face", "pname", "param"};
    static constexpr const char *pnames727[] {"face", "pname", "params"};
    static constexpr const char *pnames728[] {"face", "pname", "param"};
    static constexpr const char *pnames729[] {"face", "pname", "params"};
    static constexpr const char *pnames730[] {""};
    static constexpr const char *pnames731[] {"factor"};
    static constexpr const char *pnames732[] {"framebuffer", "mode"};
    static constexpr const char *pnames733[] {"framebuffer", "n", "bufs"};
    static constexpr const char *pnames734[] {"target", "pname", "param"};
    static constexpr const char *pnames735[] {"target", "size"};
    static constexpr const char *pnames736[] {"framebuffer", "mode"};
    static constexpr const char *pnames737[] {"target", "attachment", "renderbuffertarget", "renderbuffer"};
    static constexpr const char *pnames738[] {"target", "attachment", "renderbuffertarget", "renderbuffer"};
    static constexpr const char *pnames739[] {"target", "attachment", "renderbuffertarget", "renderbuffer"};
    static constexpr const char *pnames740[] {"target", "start", "count", "v"};
    static constexpr const char *pnames741[] {"target", "start", "count", "v"};
    static constexpr const char *pnames742[] {"target", "numsamples", "pixelindex", "values"};
    static constexpr const char *pnames743[] {"target", "attachment", "texture", "level"};
    static constexpr const char *pnames744[] {"target", "attachment", "textarget", "texture", "level"};
    static constexpr const char *pnames745[] {"target", "attachment", "textarget", "texture", "level"};
    static constexpr const char *pnames746[] {"target", "attachment", "textarget", "texture", "level"};
    static constexpr const char *pnames747[] {"target", "attachment", "textarget", "texture", "level"};
    static constexpr const char *pnames748[] {"target", "attachment", "textarget", "texture", "level", "xscale", "yscale"};
    static constexpr const char *pnames749[] {"target", "attachment", "textarget", "texture", "level", "samples"};
    static constexpr const char *pnames750[] {"target", "attachment", "textarget", "texture", "level", "samples"};
    static constexpr const char *pnames751[] {"target", "attachment", "textarget", "texture", "level"};
    static constexpr const char *pnames752[] {"target", "attachment", "textarget", "texture", "level", "zoffset"};
    static constexpr const char *pnames753[] {"target", "attachment", "textarget", "texture", "level", "zoffset"};
    static constexpr const char *pnames754[] {"target", "attachment", "textarget", "texture", "level", "zoffset"};
    static constexpr const char *pnames755[] {"target", "attachment", "texture", "level"};
    static constexpr const char *pnames756[] {"target", "attachment", "texture", "level"};
    static constexpr const char *pnames757[] {"target", "attachment", "texture", "level", "face"};
    static constexpr const char *pnames758[] {"target", "attachment", "texture", "level", "face"};
    static constexpr const char *pnames759[] {"target", "attachment", "texture", "level", "layer"};
    static constexpr const char *pnames760[] {"target", "attachment", "texture", "level", "layer"};
    static constexpr const char *pnames761[] {"target", "attachment", "texture", "level", "layer"};
    static constexpr const char *pnames762[] {"target", "attachment", "texture", "level", "layer", "xscale", "yscale"};
    static constexpr const char *pnames763[] {"target", "attachment", "texture", "level", "samples", "baseViewIndex", "numViews"};
    static constexpr const char *pnames764[] {"target", "attachment", "texture", "level", "baseViewIndex", "numViews"};
    static constexpr const char *pnames765[] {"target", "attachment", "texture", "level"};
    static constexpr const char *pnames766[] {"buffer"};
    static constexpr const char *pnames767[] {"mode"};
    static constexpr const char *pnames768[] {"left", "right", "bottom", "top", "zNear", "zFar"};
    static constexpr const char *pnames769[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames770[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames771[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames772[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames773[] {"range"};
    static constexpr const char *pnames774[] {"n", "buffers"};
    static constexpr const char *pnames775[] {"n", "buffers"};
    static constexpr const char *pnames776[] {"n", "fences"};
    static constexpr const char *pnames777[] {"n", "fences"};
    static constexpr const char *pnames778[] {"range"};
    static constexpr const char *pnames779[] {"n", "framebuffers"};
    static constexpr const char *pnames780[] {"n", "framebuffers"};
    static constexpr const char *pnames781[] {"n", "framebuffers"};
    static constexpr const char *pnames782[] {"range"};
    static constexpr const char *pnames783[] {"identifier", "num", "names"};
    static constexpr const char *pnames784[] {"n", "ids"};
    static constexpr const char *pnames785[] {"range"};
    static constexpr const char *pnames786[] {"n", "monitors"};
    static constexpr const char *pnames787[] {"n", "pipelines"};
    static constexpr const char *pnames788[] {"n", "pipelines"};
    static constexpr const char *pnames789[] {"n", "programs"};
    static constexpr const char *pnames790[] {"n", "programs"};
    static constexpr const char *pnames791[] {"n", "ids"};
    static constexpr const char *pnames792[] {"n", "ids"};
    static constexpr const char *pnames793[] {"n", "ids"};
    static constexpr const char *pnames794[] {"n", "renderbuffers"};
    static constexpr const char *pnames795[] {"n", "renderbuffers"};
    static constexpr const char *pnames796[] {"n", "renderbuffers"};
    static constexpr const char *pnames797[] {"count", "samplers"};
    static constexpr const char *pnames798[] {"datatype", "storagetype", "range", "components"};
    static constexpr const char *pnames799[] {"n", "textures"};
    static constexpr const char *pnames800[] {"n", "textures"};
    static constexpr const char *pnames801[] {"n", "ids"};
    static constexpr const char *pnames802[] {"n", "ids"};
    static constexpr const char *pnames803[] {"n", "arrays"};
    static constexpr const char *pnames804[] {"n", "arrays"};
    static constexpr const char *pnames805[] {"n", "arrays"};
    static constexpr const char *pnames806[] {"range"};
    static constexpr const char *pnames807[] {"target"};
    static constexpr const char *pnames808[] {"target"};
    static constexpr const char *pnames809[] {"target"};
    static constexpr const char *pnames810[] {"texunit", "target"};
    static constexpr const char *pnames811[] {"texture"};
    static constexpr const char *pnames812[] {"texture", "target"};
    static constexpr const char *pnames813[] {"program", "bufferIndex", "pname", "params"};
    static constexpr const char *pnames814[] {"program", "index", "bufSize", "length", "size", "type", "name"};
    static constexpr const char *pnames815[] {"programObj", "index", "maxLength", "length", "size", "type", "name"};
    static constexpr const char *pnames816[] {"program", "shadertype", "index", "bufsize", "length", "name"};
    static constexpr const char *pnames817[] {"program", "shadertype", "index", "bufsize", "length", "name"};
    static constexpr const char *pnames818[] {"program", "shadertype", "index", "pname", "values"};
    static constexpr const char *pnames819[] {"program", "index", "bufSize", "length", "size", "type", "name"};
    static constexpr const char *pnames820[] {"programObj", "index", "maxLength", "length", "size", "type", "name"};
    static constexpr const char *pnames821[] {"program", "uniformBlockIndex", "bufSize", "length", "uniformBlockName"};
    static constexpr const char *pnames822[] {"program", "uniformBlockIndex", "pname", "params"};
    static constexpr const char *pnames823[] {"program", "uniformIndex", "bufSize", "length", "uniformName"};
    static constexpr const char *pnames824[] {"program", "uniformCount", "uniformIndices", "pname", "params"};
    static constexpr const char *pnames825[] {"program", "index", "bufSize", "length", "size", "type", "name"};
    static constexpr const char *pnames826[] {"array", "pname", "params"};
    static constexpr const char *pnames827[] {"array", "pname", "params"};
    static constexpr const char *pnames828[] {"containerObj", "maxCount", "count", "obj"};
    static constexpr const char *pnames829[] {"program", "maxCount", "count", "shaders"};
    static constexpr const char *pnames830[] {"program", "name"};
    static constexpr const char *pnames831[] {"programObj", "name"};
    static constexpr const char *pnames832[] {"target", "index", "data"};
    static constexpr const char *pnames833[] {"target", "index", "data"};
    static constexpr const char *pnames834[] {"pname", "data"};
    static constexpr const char *pnames835[] {"target", "pname", "params"};
    static constexpr const char *pnames836[] {"target", "pname", "params"};
    static constexpr const char *pnames837[] {"target", "pname", "params"};
    static constexpr const char *pnames838[] {"target", "pname", "params"};
    static constexpr const char *pnames839[] {"target", "pname", "params"};
    static constexpr const char *pnames840[] {"target", "pname", "params"};
    static constexpr const char *pnames841[] {"target", "pname", "params"};
    static constexpr const char *pnames842[] {"target", "offset", "size", "data"};
    static constexpr const char *pnames843[] {"target", "offset", "size", "data"};
    static constexpr const char *pnames844[] {"plane", "equation"};
    static constexpr const char *pnames845[] {"plane", "equation"};
    static constexpr const char *pnames846[] {"plane", "equation"};
    static constexpr const char *pnames847[] {"plane", "equation"};
    static constexpr const char *pnames848[] {"plane", "equation"};
    static constexpr const char *pnames849[] {"target", "format", "type", "table"};
    static constexpr const char *pnames850[] {"target", "format", "type", "data"};
    static constexpr const char *pnames851[] {"target", "pname", "params"};
    static constexpr const char *pnames852[] {"target", "pname", "params"};
    static constexpr const char *pnames853[] {"target", "pname", "params"};
    static constexpr const char *pnames854[] {"target", "pname", "params"};
    static constexpr const char *pnames855[] {"target", "pname", "params"};
    static constexpr const char *pnames856[] {"target", "pname", "params"};
    static constexpr const char *pnames857[] {"target", "format", "type", "table"};
    static constexpr const char *pnames858[] {"stage", "portion", "variable", "pname", "params"};
    static constexpr const char *pnames859[] {"stage", "portion", "variable", "pname", "params"};
    static constexpr const char *pnames860[] {"stage", "portion", "pname", "params"};
    static constexpr const char *pnames861[] {"stage", "portion", "pname", "params"};
    static constexpr const char *pnames862[] {"stage", "pname", "params"};
    static constexpr const char *pnames863[] {"tokenID", "size"};
    static constexpr const char *pnames864[] {"texunit", "target", "lod", "img"};
    static constexpr const char *pnames865[] {"target", "level", "img"};
    static constexpr const char *pnames866[] {"target", "level", "img"};
    static constexpr const char *pnames867[] {"texture", "level", "bufSize", "pixels"};
    static constexpr const char *pnames868[] {"texture", "target", "lod", "img"};
    static constexpr const char *pnames869[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "bufSize", "pixels"};
    static constexpr const char *pnames870[] {"target", "format", "type", "image"};
    static constexpr const char *pnames871[] {"target", "format", "type", "image"};
    static constexpr const char *pnames872[] {"target", "pname", "params"};
    static constexpr const char *pnames873[] {"target", "pname", "params"};
    static constexpr const char *pnames874[] {"target", "pname", "params"};
    static constexpr const char *pnames875[] {"target", "pname", "params"};
    static constexpr const char *pnames876[] {"target", "pname", "params"};
    static constexpr const char *pnames877[] {"bufsize", "v"};
    static constexpr const char *pnames878[] {"count", "bufSize", "sources", "types", "ids", "severities", "lengths", "messageLog"};
    static constexpr const char *pnames879[] {"count", "bufsize", "categories", "severities", "ids", "lengths", "message"};
    static constexpr const char *pnames880[] {"count", "bufSize", "sources", "types", "ids", "severities", "lengths", "messageLog"};
    static constexpr const char *pnames881[] {"count", "bufSize", "sources", "types", "ids", "severities", "lengths", "messageLog"};
    static constexpr const char *pnames882[] {"target", "points"};
    static constexpr const char *pnames883[] {"target", "index", "data"};
    static constexpr const char *pnames884[] {"target", "index", "data"};
    static constexpr const char *pnames885[] {"pname", "index", "params"};
    static constexpr const char *pnames886[] {"pname", "data"};
    static constexpr const char *pnames887[] {"driverControl", "bufSize", "length", "driverControlString"};
    static constexpr const char *pnames888[] {"num", "size", "driverControls"};
    static constexpr const char *pnames889[] {""};
    static constexpr const char *pnames890[] {"fence", "pname", "params"};
    static constexpr const char *pnames891[] {"variable", "pname", "params"};
    static constexpr const char *pnames892[] {"variable", "pname", "params"};
    static constexpr const char *pnames893[] {"queryId"};
    static constexpr const char *pnames894[] {"pname", "params"};
    static constexpr const char *pnames895[] {"pname", "params"};
    static constexpr const char *pnames896[] {"target", "index", "data"};
    static constexpr const char *pnames897[] {"target", "index", "data"};
    static constexpr const char *pnames898[] {"pname", "index", "params"};
    static constexpr const char *pnames899[] {"target", "index", "data"};
    static constexpr const char *pnames900[] {"target", "index", "data"};
    static constexpr const char *pnames901[] {"pname", "data"};
    static constexpr const char *pnames902[] {"points"};
    static constexpr const char *pnames903[] {"program", "name"};
    static constexpr const char *pnames904[] {"program", "name"};
    static constexpr const char *pnames905[] {"program", "name"};
    static constexpr const char *pnames906[] {"program", "name"};
    static constexpr const char *pnames907[] {"light", "pname", "params"};
    static constexpr const char *pnames908[] {"light", "pname", "params"};
    static constexpr const char *pnames909[] {"face", "pname", "params"};
    static constexpr const char *pnames910[] {"face", "pname", "params"};
    static constexpr const char *pnames911[] {"target", "attachment", "pname", "params"};
    static constexpr const char *pnames912[] {"target", "attachment", "pname", "params"};
    static constexpr const char *pnames913[] {"target", "attachment", "pname", "params"};
    static constexpr const char *pnames914[] {"target", "pname", "numsamples", "pixelindex", "size", "values"};
    static constexpr const char *pnames915[] {"target", "pname", "params"};
    static constexpr const char *pnames916[] {"framebuffer", "pname", "params"};
    static constexpr const char *pnames917[] {"target"};
    static constexpr const char *pnames918[] {""};
    static constexpr const char *pnames919[] {""};
    static constexpr const char *pnames920[] {""};
    static constexpr const char *pnames921[] {""};
    static constexpr const char *pnames922[] {"pname"};
    static constexpr const char *pnames923[] {"target", "reset", "format", "type", "values"};
    static constexpr const char *pnames924[] {"target", "reset", "format", "type", "values"};
    static constexpr const char *pnames925[] {"target", "pname", "params"};
    static constexpr const char *pnames926[] {"target", "pname", "params"};
    static constexpr const char *pnames927[] {"target", "pname", "params"};
    static constexpr const char *pnames928[] {"target", "pname", "params"};
    static constexpr const char *pnames929[] {"target", "pname", "params"};
    static constexpr const char *pnames930[] {"texture", "level", "layered", "layer", "format"};
    static constexpr const char *pnames931[] {"texture", "level", "layered", "layer", "format"};
    static constexpr const char *pnames932[] {"target", "pname", "params"};
    static constexpr const char *pnames933[] {"target", "pname", "params"};
    static constexpr const char *pnames934[] {"obj", "maxLength", "length", "infoLog"};
    static constexpr const char *pnames935[] {""};
    static constexpr const char *pnames936[] {"target", "index", "data"};
    static constexpr const char *pnames937[] {"pname", "data"};
    static constexpr const char *pnames938[] {"pname", "params"};
    static constexpr const char *pnames939[] {"target", "index", "data"};
    static constexpr const char *pnames940[] {"target", "index", "data"};
    static constexpr const char *pnames941[] {"target", "index", "data"};
    static constexpr const char *pnames942[] {"value", "index", "result"};
    static constexpr const char *pnames943[] {"value", "result"};
    static constexpr const char *pnames944[] {"pname", "data"};
    static constexpr const char *pnames945[] {"target", "internalformat", "samples", "pname", "bufSize", "params"};
    static constexpr const char *pnames946[] {"target", "internalformat", "pname", "bufSize", "params"};
    static constexpr const char *pnames947[] {"target", "internalformat", "pname", "bufSize", "params"};
    static constexpr const char *pnames948[] {"id", "value", "data"};
    static constexpr const char *pnames949[] {"id", "value", "data"};
    static constexpr const char *pnames950[] {"id", "value", "data"};
    static constexpr const char *pnames951[] {"light", "pname", "params"};
    static constexpr const char *pnames952[] {"light", "pname", "params"};
    static constexpr const char *pnames953[] {"light", "pname", "params"};
    static constexpr const char *pnames954[] {"light", "pname", "params"};
    static constexpr const char *pnames955[] {"light", "pname", "params"};
    static constexpr const char *pnames956[] {"list", "pname", "params"};
    static constexpr const char *pnames957[] {"list", "pname", "params"};
    static constexpr const char *pnames958[] {"id", "value", "data"};
    static constexpr const char *pnames959[] {"id", "value", "data"};
    static constexpr const char *pnames960[] {"id", "value", "data"};
    static constexpr const char *pnames961[] {"target", "index", "pname", "params"};
    static constexpr const char *pnames962[] {"target", "index", "pname", "params"};
    static constexpr const char *pnames963[] {"target", "index", "type", "ustride", "vstride", "packed", "points"};
    static constexpr const char *pnames964[] {"target", "pname", "params"};
    static constexpr const char *pnames965[] {"target", "pname", "params"};
    static constexpr const char *pnames966[] {"target", "query", "v"};
    static constexpr const char *pnames967[] {"target", "query", "v"};
    static constexpr const char *pnames968[] {"target", "query", "v"};
    static constexpr const char *pnames969[] {"target", "query", "v"};
    static constexpr const char *pnames970[] {"face", "pname", "params"};
    static constexpr const char *pnames971[] {"face", "pname", "params"};
    static constexpr const char *pnames972[] {"face", "pname", "param"};
    static constexpr const char *pnames973[] {"face", "pname", "params"};
    static constexpr const char *pnames974[] {"face", "pname", "params"};
    static constexpr const char *pnames975[] {"target", "reset", "format", "type", "values"};
    static constexpr const char *pnames976[] {"target", "reset", "format", "type", "values"};
    static constexpr const char *pnames977[] {"target", "pname", "params"};
    static constexpr const char *pnames978[] {"target", "pname", "params"};
    static constexpr const char *pnames979[] {"target", "pname", "params"};
    static constexpr const char *pnames980[] {"target", "pname", "params"};
    static constexpr const char *pnames981[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames982[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames983[] {"texunit", "coord", "pname", "params"};
    static constexpr const char *pnames984[] {"texunit", "coord", "pname", "params"};
    static constexpr const char *pnames985[] {"texunit", "coord", "pname", "params"};
    static constexpr const char *pnames986[] {"texunit", "target", "level", "format", "type", "pixels"};
    static constexpr const char *pnames987[] {"texunit", "target", "level", "pname", "params"};
    static constexpr const char *pnames988[] {"texunit", "target", "level", "pname", "params"};
    static constexpr const char *pnames989[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames990[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames991[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames992[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames993[] {"pname", "index", "val"};
    static constexpr const char *pnames994[] {"pname", "index", "val"};
    static constexpr const char *pnames995[] {"buffer", "pname", "params"};
    static constexpr const char *pnames996[] {"buffer", "pname", "params"};
    static constexpr const char *pnames997[] {"buffer", "pname", "params"};
    static constexpr const char *pnames998[] {"buffer", "pname", "params"};
    static constexpr const char *pnames999[] {"buffer", "pname", "params"};
    static constexpr const char *pnames1000[] {"buffer", "pname", "params"};
    static constexpr const char *pnames1001[] {"buffer", "offset", "size", "data"};
    static constexpr const char *pnames1002[] {"buffer", "offset", "size", "data"};
    static constexpr const char *pnames1003[] {"framebuffer", "pname", "numsamples", "pixelindex", "size", "values"};
    static constexpr const char *pnames1004[] {"framebuffer", "attachment", "pname", "params"};
    static constexpr const char *pnames1005[] {"framebuffer", "attachment", "pname", "params"};
    static constexpr const char *pnames1006[] {"framebuffer", "pname", "param"};
    static constexpr const char *pnames1007[] {"framebuffer", "pname", "params"};
    static constexpr const char *pnames1008[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1009[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1010[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1011[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1012[] {"program", "target", "pname", "string"};
    static constexpr const char *pnames1013[] {"program", "target", "pname", "params"};
    static constexpr const char *pnames1014[] {"renderbuffer", "pname", "params"};
    static constexpr const char *pnames1015[] {"renderbuffer", "pname", "params"};
    static constexpr const char *pnames1016[] {"namelen", "name", "bufSize", "stringlen", "string"};
    static constexpr const char *pnames1017[] {"namelen", "name", "pname", "params"};
    static constexpr const char *pnames1018[] {"queryId", "nextQueryId"};
    static constexpr const char *pnames1019[] {"buffer", "pname", "params"};
    static constexpr const char *pnames1020[] {"buffer", "pname", "params"};
    static constexpr const char *pnames1021[] {"identifier", "name", "bufSize", "length", "label"};
    static constexpr const char *pnames1022[] {"type", "object", "bufSize", "length", "label"};
    static constexpr const char *pnames1023[] {"identifier", "name", "bufSize", "length", "label"};
    static constexpr const char *pnames1024[] {"obj", "pname", "params"};
    static constexpr const char *pnames1025[] {"objectType", "name", "pname", "params"};
    static constexpr const char *pnames1026[] {"obj", "pname", "params"};
    static constexpr const char *pnames1027[] {"ptr", "bufSize", "length", "label"};
    static constexpr const char *pnames1028[] {"ptr", "bufSize", "length", "label"};
    static constexpr const char *pnames1029[] {"id", "pname", "params"};
    static constexpr const char *pnames1030[] {"id", "pname", "params"};
    static constexpr const char *pnames1031[] {"color", "pname", "value"};
    static constexpr const char *pnames1032[] {"color", "pname", "value"};
    static constexpr const char *pnames1033[] {"path", "commands"};
    static constexpr const char *pnames1034[] {"path", "coords"};
    static constexpr const char *pnames1035[] {"path", "dashArray"};
    static constexpr const char *pnames1036[] {"path", "startSegment", "numSegments"};
    static constexpr const char *pnames1037[] {"metricQueryMask", "firstPathName", "numPaths", "stride", "metrics"};
    static constexpr const char *pnames1038[] {"metricQueryMask", "numPaths", "pathNameType", "paths", "pathBase", "stride", "metrics"};
    static constexpr const char *pnames1039[] {"path", "pname", "value"};
    static constexpr const char *pnames1040[] {"path", "pname", "value"};
    static constexpr const char *pnames1041[] {"pathListMode", "numPaths", "pathNameType", "paths", "pathBase", "advanceScale", "kerningScale", "transformType", "returnedSpacing"};
    static constexpr const char *pnames1042[] {"texCoordSet", "pname", "value"};
    static constexpr const char *pnames1043[] {"texCoordSet", "pname", "value"};
    static constexpr const char *pnames1044[] {"queryId", "counterId", "counterNameLength", "counterName", "counterDescLength", "counterDesc", "counterOffset", "counterDataSize", "counterTypeEnum", "counterDataTypeEnum", "rawCounterMaxValue"};
    static constexpr const char *pnames1045[] {"monitor", "pname", "dataSize", "data", "bytesWritten"};
    static constexpr const char *pnames1046[] {"group", "counter", "pname", "data"};
    static constexpr const char *pnames1047[] {"group", "counter", "bufSize", "length", "counterString"};
    static constexpr const char *pnames1048[] {"group", "numCounters", "maxActiveCounters", "counterSize", "counters"};
    static constexpr const char *pnames1049[] {"group", "bufSize", "length", "groupString"};
    static constexpr const char *pnames1050[] {"numGroups", "groupsSize", "groups"};
    static constexpr const char *pnames1051[] {"queryHandle", "flags", "dataSize", "data", "bytesWritten"};
    static constexpr const char *pnames1052[] {"queryName", "queryId"};
    static constexpr const char *pnames1053[] {"queryId", "queryNameLength", "queryName", "dataSize", "noCounters", "noInstances", "capsMask"};
    static constexpr const char *pnames1054[] {"map", "values"};
    static constexpr const char *pnames1055[] {"map", "values"};
    static constexpr const char *pnames1056[] {"map", "values"};
    static constexpr const char *pnames1057[] {"map", "size", "values"};
    static constexpr const char *pnames1058[] {"pname", "params"};
    static constexpr const char *pnames1059[] {"pname", "params"};
    static constexpr const char *pnames1060[] {"target", "pname", "params"};
    static constexpr const char *pnames1061[] {"target", "pname", "params"};
    static constexpr const char *pnames1062[] {"target", "index", "data"};
    static constexpr const char *pnames1063[] {"pname", "index", "params"};
    static constexpr const char *pnames1064[] {"pname", "params"};
    static constexpr const char *pnames1065[] {"pname", "params"};
    static constexpr const char *pnames1066[] {"pname", "params"};
    static constexpr const char *pnames1067[] {"mask"};
    static constexpr const char *pnames1068[] {"program", "bufSize", "length", "binaryFormat", "binary"};
    static constexpr const char *pnames1069[] {"program", "bufSize", "length", "binaryFormat", "binary"};
    static constexpr const char *pnames1070[] {"target", "index", "params"};
    static constexpr const char *pnames1071[] {"target", "index", "params"};
    static constexpr const char *pnames1072[] {"target", "index", "params"};
    static constexpr const char *pnames1073[] {"target", "index", "params"};
    static constexpr const char *pnames1074[] {"program", "bufSize", "length", "infoLog"};
    static constexpr const char *pnames1075[] {"program", "programInterface", "pname", "params"};
    static constexpr const char *pnames1076[] {"target", "index", "params"};
    static constexpr const char *pnames1077[] {"target", "index", "params"};
    static constexpr const char *pnames1078[] {"target", "index", "params"};
    static constexpr const char *pnames1079[] {"target", "index", "params"};
    static constexpr const char *pnames1080[] {"id", "len", "name", "params"};
    static constexpr const char *pnames1081[] {"id", "len", "name", "params"};
    static constexpr const char *pnames1082[] {"target", "index", "pname", "params"};
    static constexpr const char *pnames1083[] {"target", "index", "pname", "params"};
    static constexpr const char *pnames1084[] {"pipeline", "bufSize", "length", "infoLog"};
    static constexpr const char *pnames1085[] {"pipeline", "bufSize", "length", "infoLog"};
    static constexpr const char *pnames1086[] {"pipeline", "pname", "params"};
    static constexpr const char *pnames1087[] {"pipeline", "pname", "params"};
    static constexpr const char *pnames1088[] {"program", "programInterface", "name"};
    static constexpr const char *pnames1089[] {"program", "programInterface", "name"};
    static constexpr const char *pnames1090[] {"program", "programInterface", "name"};
    static constexpr const char *pnames1091[] {"program", "programInterface", "name"};
    static constexpr const char *pnames1092[] {"program", "programInterface", "index", "bufSize", "length", "name"};
    static constexpr const char *pnames1093[] {"program", "programInterface", "index", "propCount", "props", "bufSize", "length", "params"};
    static constexpr const char *pnames1094[] {"program", "programInterface", "index", "propCount", "props", "bufSize", "length", "params"};
    static constexpr const char *pnames1095[] {"program", "shadertype", "pname", "values"};
    static constexpr const char *pnames1096[] {"target", "pname", "string"};
    static constexpr const char *pnames1097[] {"id", "pname", "program"};
    static constexpr const char *pnames1098[] {"target", "index", "param"};
    static constexpr const char *pnames1099[] {"program", "pname", "params"};
    static constexpr const char *pnames1100[] {"target", "pname", "params"};
    static constexpr const char *pnames1101[] {"id", "pname", "params"};
    static constexpr const char *pnames1102[] {"id", "buffer", "pname", "offset"};
    static constexpr const char *pnames1103[] {"id", "buffer", "pname", "offset"};
    static constexpr const char *pnames1104[] {"id", "buffer", "pname", "offset"};
    static constexpr const char *pnames1105[] {"id", "buffer", "pname", "offset"};
    static constexpr const char *pnames1106[] {"target", "index", "pname", "params"};
    static constexpr const char *pnames1107[] {"id", "pname", "params"};
    static constexpr const char *pnames1108[] {"id", "pname", "params"};
    static constexpr const char *pnames1109[] {"id", "pname", "params"};
    static constexpr const char *pnames1110[] {"id", "pname", "params"};
    static constexpr const char *pnames1111[] {"id", "pname", "params"};
    static constexpr const char *pnames1112[] {"id", "pname", "params"};
    static constexpr const char *pnames1113[] {"id", "pname", "params"};
    static constexpr const char *pnames1114[] {"id", "pname", "params"};
    static constexpr const char *pnames1115[] {"id", "pname", "params"};
    static constexpr const char *pnames1116[] {"id", "pname", "params"};
    static constexpr const char *pnames1117[] {"target", "pname", "params"};
    static constexpr const char *pnames1118[] {"target", "pname", "params"};
    static constexpr const char *pnames1119[] {"target", "pname", "params"};
    static constexpr const char *pnames1120[] {"target", "pname", "params"};
    static constexpr const char *pnames1121[] {"target", "pname", "params"};
    static constexpr const char *pnames1122[] {"target", "pname", "params"};
    static constexpr const char *pnames1123[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1124[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1125[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1126[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1127[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1128[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1129[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1130[] {"sampler", "pname", "params"};
    static constexpr const char *pnames1131[] {"target", "format", "type", "row", "column", "span"};
    static constexpr const char *pnames1132[] {"target", "format", "type", "row", "column", "span"};
    static constexpr const char *pnames1133[] {"shader", "bufSize", "length", "infoLog"};
    static constexpr const char *pnames1134[] {"shadertype", "precisiontype", "range", "precision"};
    static constexpr const char *pnames1135[] {"shader", "bufSize", "length", "source"};
    static constexpr const char *pnames1136[] {"obj", "maxLength", "length", "source"};
    static constexpr const char *pnames1137[] {"shader", "pname", "params"};
    static constexpr const char *pnames1138[] {"target", "points"};
    static constexpr const char *pnames1139[] {"shadertype"};
    static constexpr const char *pnames1140[] {"name"};
    static constexpr const char *pnames1141[] {"name", "index"};
    static constexpr const char *pnames1142[] {"program", "shadertype", "name"};
    static constexpr const char *pnames1143[] {"program", "shadertype", "name"};
    static constexpr const char *pnames1144[] {"sync", "pname", "bufSize", "length", "values"};
    static constexpr const char *pnames1145[] {"sync", "pname", "bufSize", "length", "values"};
    static constexpr const char *pnames1146[] {"pname", "param"};
    static constexpr const char *pnames1147[] {"pname", "param"};
    static constexpr const char *pnames1148[] {"target", "pname", "params"};
    static constexpr const char *pnames1149[] {"target", "pname", "params"};
    static constexpr const char *pnames1150[] {"target", "pname", "params"};
    static constexpr const char *pnames1151[] {"target", "pname", "params"};
    static constexpr const char *pnames1152[] {"target", "filter", "weights"};
    static constexpr const char *pnames1153[] {"coord", "pname", "params"};
    static constexpr const char *pnames1154[] {"coord", "pname", "params"};
    static constexpr const char *pnames1155[] {"coord", "pname", "params"};
    static constexpr const char *pnames1156[] {"coord", "pname", "params"};
    static constexpr const char *pnames1157[] {"coord", "pname", "params"};
    static constexpr const char *pnames1158[] {"coord", "pname", "params"};
    static constexpr const char *pnames1159[] {"target", "level", "format", "type", "pixels"};
    static constexpr const char *pnames1160[] {"target", "level", "pname", "params"};
    static constexpr const char *pnames1161[] {"target", "level", "pname", "params"};
    static constexpr const char *pnames1162[] {"target", "level", "pname", "params"};
    static constexpr const char *pnames1163[] {"target", "pname", "params"};
    static constexpr const char *pnames1164[] {"target", "pname", "params"};
    static constexpr const char *pnames1165[] {"target", "pname", "params"};
    static constexpr const char *pnames1166[] {"target", "pname", "params"};
    static constexpr const char *pnames1167[] {"target", "pname", "params"};
    static constexpr const char *pnames1168[] {"target", "pname", "params"};
    static constexpr const char *pnames1169[] {"target", "pname", "params"};
    static constexpr const char *pnames1170[] {"target", "pname", "params"};
    static constexpr const char *pnames1171[] {"target", "pname", "params"};
    static constexpr const char *pnames1172[] {"target", "pname", "params"};
    static constexpr const char *pnames1173[] {"target", "pname", "params"};
    static constexpr const char *pnames1174[] {"texture"};
    static constexpr const char *pnames1175[] {"texture"};
    static constexpr const char *pnames1176[] {"texture"};
    static constexpr const char *pnames1177[] {"texture", "level", "format", "type", "bufSize", "pixels"};
    static constexpr const char *pnames1178[] {"texture", "target", "level", "format", "type", "pixels"};
    static constexpr const char *pnames1179[] {"texture", "level", "pname", "params"};
    static constexpr const char *pnames1180[] {"texture", "target", "level", "pname", "params"};
    static constexpr const char *pnames1181[] {"texture", "level", "pname", "params"};
    static constexpr const char *pnames1182[] {"texture", "target", "level", "pname", "params"};
    static constexpr const char *pnames1183[] {"texture", "pname", "params"};
    static constexpr const char *pnames1184[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames1185[] {"texture", "pname", "params"};
    static constexpr const char *pnames1186[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames1187[] {"texture", "pname", "params"};
    static constexpr const char *pnames1188[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames1189[] {"texture", "pname", "params"};
    static constexpr const char *pnames1190[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames1191[] {"texture", "sampler"};
    static constexpr const char *pnames1192[] {"texture", "sampler"};
    static constexpr const char *pnames1193[] {"texture", "sampler"};
    static constexpr const char *pnames1194[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "bufSize", "pixels"};
    static constexpr const char *pnames1195[] {"target", "address", "pname", "params"};
    static constexpr const char *pnames1196[] {"program", "index", "bufSize", "length", "size", "type", "name"};
    static constexpr const char *pnames1197[] {"program", "index", "bufSize", "length", "size", "type", "name"};
    static constexpr const char *pnames1198[] {"program", "index", "location"};
    static constexpr const char *pnames1199[] {"xfb", "pname", "index", "param"};
    static constexpr const char *pnames1200[] {"xfb", "pname", "index", "param"};
    static constexpr const char *pnames1201[] {"xfb", "pname", "param"};
    static constexpr const char *pnames1202[] {"shader", "bufsize", "length", "source"};
    static constexpr const char *pnames1203[] {"program", "uniformBlockName"};
    static constexpr const char *pnames1204[] {"program", "location"};
    static constexpr const char *pnames1205[] {"program", "uniformCount", "uniformNames", "uniformIndices"};
    static constexpr const char *pnames1206[] {"program", "name"};
    static constexpr const char *pnames1207[] {"programObj", "name"};
    static constexpr const char *pnames1208[] {"program", "location"};
    static constexpr const char *pnames1209[] {"shadertype", "location", "params"};
    static constexpr const char *pnames1210[] {"program", "location", "params"};
    static constexpr const char *pnames1211[] {"program", "location", "params"};
    static constexpr const char *pnames1212[] {"programObj", "location", "params"};
    static constexpr const char *pnames1213[] {"program", "location", "params"};
    static constexpr const char *pnames1214[] {"program", "location", "params"};
    static constexpr const char *pnames1215[] {"program", "location", "params"};
    static constexpr const char *pnames1216[] {"programObj", "location", "params"};
    static constexpr const char *pnames1217[] {"program", "location", "params"};
    static constexpr const char *pnames1218[] {"program", "location", "params"};
    static constexpr const char *pnames1219[] {"program", "location", "params"};
    static constexpr const char *pnames1220[] {"program", "location", "params"};
    static constexpr const char *pnames1221[] {"id", "pname", "params"};
    static constexpr const char *pnames1222[] {"id", "pname", "params"};
    static constexpr const char *pnames1223[] {"id", "value", "data"};
    static constexpr const char *pnames1224[] {"id", "value", "data"};
    static constexpr const char *pnames1225[] {"id", "value", "data"};
    static constexpr const char *pnames1226[] {"id", "value", "data"};
    static constexpr const char *pnames1227[] {"program", "name"};
    static constexpr const char *pnames1228[] {"vaobj", "index", "pname", "param"};
    static constexpr const char *pnames1229[] {"vaobj", "index", "pname", "param"};
    static constexpr const char *pnames1230[] {"vaobj", "index", "pname", "param"};
    static constexpr const char *pnames1231[] {"vaobj", "pname", "param"};
    static constexpr const char *pnames1232[] {"vaobj", "index", "pname", "param"};
    static constexpr const char *pnames1233[] {"vaobj", "pname", "param"};
    static constexpr const char *pnames1234[] {"vaobj", "pname", "param"};
    static constexpr const char *pnames1235[] {"index", "pname", "params"};
    static constexpr const char *pnames1236[] {"index", "pname", "params"};
    static constexpr const char *pnames1237[] {"index", "pname", "params"};
    static constexpr const char *pnames1238[] {"index", "pname", "params"};
    static constexpr const char *pnames1239[] {"index", "pname", "params"};
    static constexpr const char *pnames1240[] {"index", "pname", "params"};
    static constexpr const char *pnames1241[] {"index", "pname", "params"};
    static constexpr const char *pnames1242[] {"index", "pname", "params"};
    static constexpr const char *pnames1243[] {"index", "pname", "params"};
    static constexpr const char *pnames1244[] {"index", "pname", "params"};
    static constexpr const char *pnames1245[] {"index", "pname", "params"};
    static constexpr const char *pnames1246[] {"index", "pname", "pointer"};
    static constexpr const char *pnames1247[] {"index", "pname", "pointer"};
    static constexpr const char *pnames1248[] {"index", "pname", "pointer"};
    static constexpr const char *pnames1249[] {"index", "pname", "params"};
    static constexpr const char *pnames1250[] {"index", "pname", "params"};
    static constexpr const char *pnames1251[] {"index", "pname", "params"};
    static constexpr const char *pnames1252[] {"index", "pname", "params"};
    static constexpr const char *pnames1253[] {"index", "pname", "params"};
    static constexpr const char *pnames1254[] {"index", "pname", "params"};
    static constexpr const char *pnames1255[] {"index", "pname", "params"};
    static constexpr const char *pnames1256[] {"index", "pname", "params"};
    static constexpr const char *pnames1257[] {"index", "pname", "params"};
    static constexpr const char *pnames1258[] {"video_capture_slot", "stream", "pname", "params"};
    static constexpr const char *pnames1259[] {"video_capture_slot", "stream", "pname", "params"};
    static constexpr const char *pnames1260[] {"video_capture_slot", "stream", "pname", "params"};
    static constexpr const char *pnames1261[] {"video_capture_slot", "pname", "params"};
    static constexpr const char *pnames1262[] {"video_slot", "pname", "params"};
    static constexpr const char *pnames1263[] {"video_slot", "pname", "params"};
    static constexpr const char *pnames1264[] {"video_slot", "pname", "params"};
    static constexpr const char *pnames1265[] {"video_slot", "pname", "params"};
    static constexpr const char *pnames1266[] {"target", "format", "type", "bufSize", "table"};
    static constexpr const char *pnames1267[] {"target", "format", "type", "bufSize", "table"};
    static constexpr const char *pnames1268[] {"target", "lod", "bufSize", "pixels"};
    static constexpr const char *pnames1269[] {"target", "lod", "bufSize", "img"};
    static constexpr const char *pnames1270[] {"target", "format", "type", "bufSize", "image"};
    static constexpr const char *pnames1271[] {"target", "format", "type", "bufSize", "image"};
    static constexpr const char *pnames1272[] {"target", "reset", "format", "type", "bufSize", "values"};
    static constexpr const char *pnames1273[] {"target", "reset", "format", "type", "bufSize", "values"};
    static constexpr const char *pnames1274[] {"target", "query", "bufSize", "v"};
    static constexpr const char *pnames1275[] {"target", "query", "bufSize", "v"};
    static constexpr const char *pnames1276[] {"target", "query", "bufSize", "v"};
    static constexpr const char *pnames1277[] {"target", "query", "bufSize", "v"};
    static constexpr const char *pnames1278[] {"target", "query", "bufSize", "v"};
    static constexpr const char *pnames1279[] {"target", "query", "bufSize", "v"};
    static constexpr const char *pnames1280[] {"target", "reset", "format", "type", "bufSize", "values"};
    static constexpr const char *pnames1281[] {"target", "reset", "format", "type", "bufSize", "values"};
    static constexpr const char *pnames1282[] {"map", "bufSize", "values"};
    static constexpr const char *pnames1283[] {"map", "bufSize", "values"};
    static constexpr const char *pnames1284[] {"map", "bufSize", "values"};
    static constexpr const char *pnames1285[] {"map", "bufSize", "values"};
    static constexpr const char *pnames1286[] {"map", "bufSize", "values"};
    static constexpr const char *pnames1287[] {"map", "bufSize", "values"};
    static constexpr const char *pnames1288[] {"bufSize", "pattern"};
    static constexpr const char *pnames1289[] {"bufSize", "pattern"};
    static constexpr const char *pnames1290[] {"target", "format", "type", "rowBufSize", "row", "columnBufSize", "column", "span"};
    static constexpr const char *pnames1291[] {"target", "format", "type", "rowBufSize", "row", "columnBufSize", "column", "span"};
    static constexpr const char *pnames1292[] {"target", "level", "format", "type", "bufSize", "pixels"};
    static constexpr const char *pnames1293[] {"target", "level", "format", "type", "bufSize", "img"};
    static constexpr const char *pnames1294[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1295[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1296[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1297[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1298[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1299[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1300[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1301[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1302[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1303[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1304[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1305[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1306[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1307[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1308[] {"program", "location", "bufSize", "params"};
    static constexpr const char *pnames1309[] {"factor"};
    static constexpr const char *pnames1310[] {"factor"};
    static constexpr const char *pnames1311[] {"factor"};
    static constexpr const char *pnames1312[] {"factor"};
    static constexpr const char *pnames1313[] {"factor"};
    static constexpr const char *pnames1314[] {"factor"};
    static constexpr const char *pnames1315[] {"factor"};
    static constexpr const char *pnames1316[] {"factor"};
    static constexpr const char *pnames1317[] {"target", "mode"};
    static constexpr const char *pnames1318[] {"target", "mode"};
    static constexpr const char *pnames1319[] {"target", "width", "internalformat", "sink"};
    static constexpr const char *pnames1320[] {"target", "width", "internalformat", "sink"};
    static constexpr const char *pnames1321[] {"pname", "params"};
    static constexpr const char *pnames1322[] {"target", "pname", "param"};
    static constexpr const char *pnames1323[] {"target", "pname", "params"};
    static constexpr const char *pnames1324[] {"target", "pname", "param"};
    static constexpr const char *pnames1325[] {"target", "pname", "params"};
    static constexpr const char *pnames1326[] {"external_sync_type", "external_sync", "flags"};
    static constexpr const char *pnames1327[] {"type", "stride"};
    static constexpr const char *pnames1328[] {"func", "ref"};
    static constexpr const char *pnames1329[] {"mask"};
    static constexpr const char *pnames1330[] {"face", "mode"};
    static constexpr const char *pnames1331[] {"type", "stride", "pointer"};
    static constexpr const char *pnames1332[] {"type", "stride", "count", "pointer"};
    static constexpr const char *pnames1333[] {"type", "stride", "pointer", "ptrstride"};
    static constexpr const char *pnames1334[] {"c"};
    static constexpr const char *pnames1335[] {"c"};
    static constexpr const char *pnames1336[] {"c"};
    static constexpr const char *pnames1337[] {"c"};
    static constexpr const char *pnames1338[] {"c"};
    static constexpr const char *pnames1339[] {"c"};
    static constexpr const char *pnames1340[] {"c"};
    static constexpr const char *pnames1341[] {"c"};
    static constexpr const char *pnames1342[] {"c"};
    static constexpr const char *pnames1343[] {"c"};
    static constexpr const char *pnames1344[] {"component"};
    static constexpr const char *pnames1345[] {"component"};
    static constexpr const char *pnames1346[] {""};
    static constexpr const char *pnames1347[] {"res", "src", "num"};
    static constexpr const char *pnames1348[] {"length", "marker"};
    static constexpr const char *pnames1349[] {"size", "buffer"};
    static constexpr const char *pnames1350[] {"format", "stride", "pointer"};
    static constexpr const char *pnames1351[] {"resultPath", "pathA", "pathB", "weight"};
    static constexpr const char *pnames1352[] {"buffer"};
    static constexpr const char *pnames1353[] {"buffer", "offset", "length"};
    static constexpr const char *pnames1354[] {"target", "numAttachments", "attachments"};
    static constexpr const char *pnames1355[] {"framebuffer", "numAttachments", "attachments"};
    static constexpr const char *pnames1356[] {"framebuffer", "numAttachments", "attachments", "x", "y", "width", "height"};
    static constexpr const char *pnames1357[] {"target", "numAttachments", "attachments", "x", "y", "width", "height"};
    static constexpr const char *pnames1358[] {"texture", "level"};
    static constexpr const char *pnames1359[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth"};
    static constexpr const char *pnames1360[] {"marker"};
    static constexpr const char *pnames1361[] {"buffer"};
    static constexpr const char *pnames1362[] {"buffer"};
    static constexpr const char *pnames1363[] {"target"};
    static constexpr const char *pnames1364[] {"list"};
    static constexpr const char *pnames1365[] {"cap"};
    static constexpr const char *pnames1366[] {"target", "index"};
    static constexpr const char *pnames1367[] {"target", "index"};
    static constexpr const char *pnames1368[] {"target", "index"};
    static constexpr const char *pnames1369[] {"target", "index"};
    static constexpr const char *pnames1370[] {"target", "index"};
    static constexpr const char *pnames1371[] {"fence"};
    static constexpr const char *pnames1372[] {"fence"};
    static constexpr const char *pnames1373[] {"framebuffer"};
    static constexpr const char *pnames1374[] {"framebuffer"};
    static constexpr const char *pnames1375[] {"framebuffer"};
    static constexpr const char *pnames1376[] {"handle"};
    static constexpr const char *pnames1377[] {"handle"};
    static constexpr const char *pnames1378[] {"list"};
    static constexpr const char *pnames1379[] {"identifier", "name"};
    static constexpr const char *pnames1380[] {"buffer"};
    static constexpr const char *pnames1381[] {"namelen", "name"};
    static constexpr const char *pnames1382[] {"buffer"};
    static constexpr const char *pnames1383[] {"id"};
    static constexpr const char *pnames1384[] {"path"};
    static constexpr const char *pnames1385[] {"path", "mask", "x", "y"};
    static constexpr const char *pnames1386[] {"path", "x", "y"};
    static constexpr const char *pnames1387[] {"program"};
    static constexpr const char *pnames1388[] {"program"};
    static constexpr const char *pnames1389[] {"id"};
    static constexpr const char *pnames1390[] {"pipeline"};
    static constexpr const char *pnames1391[] {"pipeline"};
    static constexpr const char *pnames1392[] {"id"};
    static constexpr const char *pnames1393[] {"id"};
    static constexpr const char *pnames1394[] {"id"};
    static constexpr const char *pnames1395[] {"renderbuffer"};
    static constexpr const char *pnames1396[] {"renderbuffer"};
    static constexpr const char *pnames1397[] {"renderbuffer"};
    static constexpr const char *pnames1398[] {"sampler"};
    static constexpr const char *pnames1399[] {"shader"};
    static constexpr const char *pnames1400[] {"state"};
    static constexpr const char *pnames1401[] {"sync"};
    static constexpr const char *pnames1402[] {"sync"};
    static constexpr const char *pnames1403[] {"texture"};
    static constexpr const char *pnames1404[] {"texture"};
    static constexpr const char *pnames1405[] {"handle"};
    static constexpr const char *pnames1406[] {"handle"};
    static constexpr const char *pnames1407[] {"id"};
    static constexpr const char *pnames1408[] {"id"};
    static constexpr const char *pnames1409[] {"id", "cap"};
    static constexpr const char *pnames1410[] {"array"};
    static constexpr const char *pnames1411[] {"array"};
    static constexpr const char *pnames1412[] {"array"};
    static constexpr const char *pnames1413[] {"index", "pname"};
    static constexpr const char *pnames1414[] {"type", "object", "length", "label"};
    static constexpr const char *pnames1415[] {"pname", "param"};
    static constexpr const char *pnames1416[] {"pname", "param"};
    static constexpr const char *pnames1417[] {"pname", "params"};
    static constexpr const char *pnames1418[] {"pname", "param"};
    static constexpr const char *pnames1419[] {"pname", "params"};
    static constexpr const char *pnames1420[] {"pname", "param"};
    static constexpr const char *pnames1421[] {"pname", "param"};
    static constexpr const char *pnames1422[] {"pname", "param"};
    static constexpr const char *pnames1423[] {"pname", "param"};
    static constexpr const char *pnames1424[] {"light", "pname", "param"};
    static constexpr const char *pnames1425[] {"light", "pname", "params"};
    static constexpr const char *pnames1426[] {"light", "pname", "param"};
    static constexpr const char *pnames1427[] {"light", "pname", "params"};
    static constexpr const char *pnames1428[] {"light", "pname", "param"};
    static constexpr const char *pnames1429[] {"light", "pname", "param"};
    static constexpr const char *pnames1430[] {"light", "pname", "params"};
    static constexpr const char *pnames1431[] {"light", "pname", "params"};
    static constexpr const char *pnames1432[] {"factor", "pattern"};
    static constexpr const char *pnames1433[] {"width"};
    static constexpr const char *pnames1434[] {"width"};
    static constexpr const char *pnames1435[] {"width"};
    static constexpr const char *pnames1436[] {"program"};
    static constexpr const char *pnames1437[] {"programObj"};
    static constexpr const char *pnames1438[] {"base"};
    static constexpr const char *pnames1439[] {"list", "segment", "indirects", "sizes", "states", "fbos", "count"};
    static constexpr const char *pnames1440[] {"list", "pname", "param"};
    static constexpr const char *pnames1441[] {"list", "pname", "params"};
    static constexpr const char *pnames1442[] {"list", "pname", "param"};
    static constexpr const char *pnames1443[] {"list", "pname", "params"};
    static constexpr const char *pnames1444[] {""};
    static constexpr const char *pnames1445[] {"mask"};
    static constexpr const char *pnames1446[] {"m"};
    static constexpr const char *pnames1447[] {"m"};
    static constexpr const char *pnames1448[] {"m"};
    static constexpr const char *pnames1449[] {"m"};
    static constexpr const char *pnames1450[] {"name"};
    static constexpr const char *pnames1451[] {""};
    static constexpr const char *pnames1452[] {"target", "id", "len", "program"};
    static constexpr const char *pnames1453[] {"m"};
    static constexpr const char *pnames1454[] {"m"};
    static constexpr const char *pnames1455[] {"m"};
    static constexpr const char *pnames1456[] {"m"};
    static constexpr const char *pnames1457[] {"m"};
    static constexpr const char *pnames1458[] {"first", "count"};
    static constexpr const char *pnames1459[] {"opcode"};
    static constexpr const char *pnames1460[] {"target"};
    static constexpr const char *pnames1461[] {"target", "access"};
    static constexpr const char *pnames1462[] {"handle"};
    static constexpr const char *pnames1463[] {"handle"};
    static constexpr const char *pnames1464[] {"handle", "access"};
    static constexpr const char *pnames1465[] {"handle", "access"};
    static constexpr const char *pnames1466[] {"buffer"};
    static constexpr const char *pnames1467[] {"buffer", "access"};
    static constexpr const char *pnames1468[] {"handle"};
    static constexpr const char *pnames1469[] {"handle"};
    static constexpr const char *pnames1470[] {"handle"};
    static constexpr const char *pnames1471[] {"handle"};
    static constexpr const char *pnames1472[] {"target", "u1", "u2", "stride", "order", "points"};
    static constexpr const char *pnames1473[] {"target", "u1", "u2", "stride", "order", "points"};
    static constexpr const char *pnames1474[] {"target", "u1", "u2", "stride", "order", "points"};
    static constexpr const char *pnames1475[] {"target", "u1", "u2", "ustride", "uorder", "v1", "v2", "vstride", "vorder", "points"};
    static constexpr const char *pnames1476[] {"target", "u1", "u2", "ustride", "uorder", "v1", "v2", "vstride", "vorder", "points"};
    static constexpr const char *pnames1477[] {"target", "u1", "u2", "ustride", "uorder", "v1", "v2", "vstride", "vorder", "points"};
    static constexpr const char *pnames1478[] {"target", "access"};
    static constexpr const char *pnames1479[] {"target", "access"};
    static constexpr const char *pnames1480[] {"target", "access"};
    static constexpr const char *pnames1481[] {"target", "offset", "length", "access"};
    static constexpr const char *pnames1482[] {"target", "offset", "length", "access"};
    static constexpr const char *pnames1483[] {"target", "index", "type", "ustride", "vstride", "uorder", "vorder", "packed", "points"};
    static constexpr const char *pnames1484[] {"un", "u1", "u2"};
    static constexpr const char *pnames1485[] {"un", "u1", "u2"};
    static constexpr const char *pnames1486[] {"n", "u1", "u2"};
    static constexpr const char *pnames1487[] {"un", "u1", "u2", "vn", "v1", "v2"};
    static constexpr const char *pnames1488[] {"un", "u1", "u2", "vn", "v1", "v2"};
    static constexpr const char *pnames1489[] {"n", "u1", "u2", "v1", "v2"};
    static constexpr const char *pnames1490[] {"buffer", "access"};
    static constexpr const char *pnames1491[] {"buffer", "access"};
    static constexpr const char *pnames1492[] {"buffer", "offset", "length", "access"};
    static constexpr const char *pnames1493[] {"buffer", "offset", "length", "access"};
    static constexpr const char *pnames1494[] {"buffer"};
    static constexpr const char *pnames1495[] {"target", "pname", "params"};
    static constexpr const char *pnames1496[] {"target", "pname", "params"};
    static constexpr const char *pnames1497[] {"texture", "level", "access", "stride", "layout"};
    static constexpr const char *pnames1498[] {"index", "size", "u1", "u2", "stride", "order", "points"};
    static constexpr const char *pnames1499[] {"index", "size", "u1", "u2", "stride", "order", "points"};
    static constexpr const char *pnames1500[] {"index", "size", "u1", "u2", "ustride", "uorder", "v1", "v2", "vstride", "vorder", "points"};
    static constexpr const char *pnames1501[] {"index", "size", "u1", "u2", "ustride", "uorder", "v1", "v2", "vstride", "vorder", "points"};
    static constexpr const char *pnames1502[] {"face", "pname", "param"};
    static constexpr const char *pnames1503[] {"face", "pname", "params"};
    static constexpr const char *pnames1504[] {"face", "pname", "param"};
    static constexpr const char *pnames1505[] {"face", "pname", "params"};
    static constexpr const char *pnames1506[] {"face", "pname", "param"};
    static constexpr const char *pnames1507[] {"face", "pname", "param"};
    static constexpr const char *pnames1508[] {"face", "pname", "param"};
    static constexpr const char *pnames1509[] {"face", "pname", "param"};
    static constexpr const char *pnames1510[] {"mode", "left", "right", "bottom", "top", "zNear", "zFar"};
    static constexpr const char *pnames1511[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames1512[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames1513[] {"size", "indices"};
    static constexpr const char *pnames1514[] {"size", "indices"};
    static constexpr const char *pnames1515[] {"size", "indices"};
    static constexpr const char *pnames1516[] {"matrixMode", "m"};
    static constexpr const char *pnames1517[] {"matrixMode", "m"};
    static constexpr const char *pnames1518[] {"mode"};
    static constexpr const char *pnames1519[] {"matrixMode", "m"};
    static constexpr const char *pnames1520[] {"mode", "m"};
    static constexpr const char *pnames1521[] {"mode", "m"};
    static constexpr const char *pnames1522[] {"mode", "m"};
    static constexpr const char *pnames1523[] {"mode", "m"};
    static constexpr const char *pnames1524[] {"mode"};
    static constexpr const char *pnames1525[] {"matrixMode", "m"};
    static constexpr const char *pnames1526[] {"matrixMode", "m"};
    static constexpr const char *pnames1527[] {"matrixMode", "m"};
    static constexpr const char *pnames1528[] {"mode", "m"};
    static constexpr const char *pnames1529[] {"mode", "m"};
    static constexpr const char *pnames1530[] {"mode", "m"};
    static constexpr const char *pnames1531[] {"mode", "m"};
    static constexpr const char *pnames1532[] {"mode", "left", "right", "bottom", "top", "zNear", "zFar"};
    static constexpr const char *pnames1533[] {"mode"};
    static constexpr const char *pnames1534[] {"mode"};
    static constexpr const char *pnames1535[] {"mode", "angle", "x", "y", "z"};
    static constexpr const char *pnames1536[] {"mode", "angle", "x", "y", "z"};
    static constexpr const char *pnames1537[] {"mode", "x", "y", "z"};
    static constexpr const char *pnames1538[] {"mode", "x", "y", "z"};
    static constexpr const char *pnames1539[] {"mode", "x", "y", "z"};
    static constexpr const char *pnames1540[] {"mode", "x", "y", "z"};
    static constexpr const char *pnames1541[] {"count"};
    static constexpr const char *pnames1542[] {"barriers"};
    static constexpr const char *pnames1543[] {"barriers"};
    static constexpr const char *pnames1544[] {"barriers"};
    static constexpr const char *pnames1545[] {"value"};
    static constexpr const char *pnames1546[] {"value"};
    static constexpr const char *pnames1547[] {"value"};
    static constexpr const char *pnames1548[] {"target", "internalformat", "sink"};
    static constexpr const char *pnames1549[] {"target", "internalformat", "sink"};
    static constexpr const char *pnames1550[] {"m"};
    static constexpr const char *pnames1551[] {"m"};
    static constexpr const char *pnames1552[] {"m"};
    static constexpr const char *pnames1553[] {"m"};
    static constexpr const char *pnames1554[] {"m"};
    static constexpr const char *pnames1555[] {"m"};
    static constexpr const char *pnames1556[] {"m"};
    static constexpr const char *pnames1557[] {"m"};
    static constexpr const char *pnames1558[] {"m"};
    static constexpr const char *pnames1559[] {"mode", "first", "count", "drawcount"};
    static constexpr const char *pnames1560[] {"mode", "first", "count", "primcount"};
    static constexpr const char *pnames1561[] {"mode", "indirect", "drawcount", "stride"};
    static constexpr const char *pnames1562[] {"mode", "indirect", "primcount", "stride"};
    static constexpr const char *pnames1563[] {"mode", "indirect", "drawCount", "maxDrawCount", "stride", "vertexBufferCount"};
    static constexpr const char *pnames1564[] {"mode", "indirect", "drawCount", "stride", "vertexBufferCount"};
    static constexpr const char *pnames1565[] {"mode", "indirect", "drawcount", "maxdrawcount", "stride"};
    static constexpr const char *pnames1566[] {"mode", "indirect", "drawcount", "stride"};
    static constexpr const char *pnames1567[] {"mode", "first", "count", "primcount"};
    static constexpr const char *pnames1568[] {"mode", "count", "type", "indices", "drawcount"};
    static constexpr const char *pnames1569[] {"mode", "count", "type", "indices", "drawcount", "basevertex"};
    static constexpr const char *pnames1570[] {"mode", "count", "type", "indices", "primcount", "basevertex"};
    static constexpr const char *pnames1571[] {"mode", "count", "type", "indices", "primcount", "basevertex"};
    static constexpr const char *pnames1572[] {"mode", "count", "type", "indices", "primcount"};
    static constexpr const char *pnames1573[] {"mode", "type", "indirect", "drawcount", "stride"};
    static constexpr const char *pnames1574[] {"mode", "type", "indirect", "primcount", "stride"};
    static constexpr const char *pnames1575[] {"mode", "type", "indirect", "drawCount", "maxDrawCount", "stride", "vertexBufferCount"};
    static constexpr const char *pnames1576[] {"mode", "type", "indirect", "drawCount", "stride", "vertexBufferCount"};
    static constexpr const char *pnames1577[] {"mode", "type", "indirect", "drawcount", "maxdrawcount", "stride"};
    static constexpr const char *pnames1578[] {"mode", "type", "indirect", "drawcount", "stride"};
    static constexpr const char *pnames1579[] {"mode", "start", "end", "first", "count", "primcount"};
    static constexpr const char *pnames1580[] {"mode", "first", "count", "primcount", "modestride"};
    static constexpr const char *pnames1581[] {"mode", "count", "type", "indices", "primcount", "modestride"};
    static constexpr const char *pnames1582[] {"texunit", "target", "internalformat", "buffer"};
    static constexpr const char *pnames1583[] {"texture", "s"};
    static constexpr const char *pnames1584[] {"texture", "coords"};
    static constexpr const char *pnames1585[] {"target", "s"};
    static constexpr const char *pnames1586[] {"target", "s"};
    static constexpr const char *pnames1587[] {"target", "v"};
    static constexpr const char *pnames1588[] {"target", "v"};
    static constexpr const char *pnames1589[] {"target", "s"};
    static constexpr const char *pnames1590[] {"target", "s"};
    static constexpr const char *pnames1591[] {"target", "v"};
    static constexpr const char *pnames1592[] {"target", "v"};
    static constexpr const char *pnames1593[] {"target", "s"};
    static constexpr const char *pnames1594[] {"target", "v"};
    static constexpr const char *pnames1595[] {"target", "s"};
    static constexpr const char *pnames1596[] {"target", "s"};
    static constexpr const char *pnames1597[] {"target", "v"};
    static constexpr const char *pnames1598[] {"target", "v"};
    static constexpr const char *pnames1599[] {"target", "s"};
    static constexpr const char *pnames1600[] {"target", "s"};
    static constexpr const char *pnames1601[] {"target", "v"};
    static constexpr const char *pnames1602[] {"target", "v"};
    static constexpr const char *pnames1603[] {"texture", "s"};
    static constexpr const char *pnames1604[] {"texture", "coords"};
    static constexpr const char *pnames1605[] {"texture", "s", "t"};
    static constexpr const char *pnames1606[] {"texture", "coords"};
    static constexpr const char *pnames1607[] {"target", "s", "t"};
    static constexpr const char *pnames1608[] {"target", "s", "t"};
    static constexpr const char *pnames1609[] {"target", "v"};
    static constexpr const char *pnames1610[] {"target", "v"};
    static constexpr const char *pnames1611[] {"target", "s", "t"};
    static constexpr const char *pnames1612[] {"target", "s", "t"};
    static constexpr const char *pnames1613[] {"target", "v"};
    static constexpr const char *pnames1614[] {"target", "v"};
    static constexpr const char *pnames1615[] {"target", "s", "t"};
    static constexpr const char *pnames1616[] {"target", "v"};
    static constexpr const char *pnames1617[] {"target", "s", "t"};
    static constexpr const char *pnames1618[] {"target", "s", "t"};
    static constexpr const char *pnames1619[] {"target", "v"};
    static constexpr const char *pnames1620[] {"target", "v"};
    static constexpr const char *pnames1621[] {"target", "s", "t"};
    static constexpr const char *pnames1622[] {"target", "s", "t"};
    static constexpr const char *pnames1623[] {"target", "v"};
    static constexpr const char *pnames1624[] {"target", "v"};
    static constexpr const char *pnames1625[] {"texture", "s", "t"};
    static constexpr const char *pnames1626[] {"texture", "coords"};
    static constexpr const char *pnames1627[] {"texture", "s", "t", "r"};
    static constexpr const char *pnames1628[] {"texture", "coords"};
    static constexpr const char *pnames1629[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1630[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1631[] {"target", "v"};
    static constexpr const char *pnames1632[] {"target", "v"};
    static constexpr const char *pnames1633[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1634[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1635[] {"target", "v"};
    static constexpr const char *pnames1636[] {"target", "v"};
    static constexpr const char *pnames1637[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1638[] {"target", "v"};
    static constexpr const char *pnames1639[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1640[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1641[] {"target", "v"};
    static constexpr const char *pnames1642[] {"target", "v"};
    static constexpr const char *pnames1643[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1644[] {"target", "s", "t", "r"};
    static constexpr const char *pnames1645[] {"target", "v"};
    static constexpr const char *pnames1646[] {"target", "v"};
    static constexpr const char *pnames1647[] {"texture", "s", "t", "r"};
    static constexpr const char *pnames1648[] {"texture", "coords"};
    static constexpr const char *pnames1649[] {"texture", "s", "t", "r", "q"};
    static constexpr const char *pnames1650[] {"texture", "coords"};
    static constexpr const char *pnames1651[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1652[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1653[] {"target", "v"};
    static constexpr const char *pnames1654[] {"target", "v"};
    static constexpr const char *pnames1655[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1656[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1657[] {"target", "v"};
    static constexpr const char *pnames1658[] {"target", "v"};
    static constexpr const char *pnames1659[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1660[] {"target", "v"};
    static constexpr const char *pnames1661[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1662[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1663[] {"target", "v"};
    static constexpr const char *pnames1664[] {"target", "v"};
    static constexpr const char *pnames1665[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1666[] {"target", "s", "t", "r", "q"};
    static constexpr const char *pnames1667[] {"target", "v"};
    static constexpr const char *pnames1668[] {"target", "v"};
    static constexpr const char *pnames1669[] {"texture", "s", "t", "r", "q"};
    static constexpr const char *pnames1670[] {"texture", "s", "t", "r", "q"};
    static constexpr const char *pnames1671[] {"texture", "coords"};
    static constexpr const char *pnames1672[] {"texture", "type", "coords"};
    static constexpr const char *pnames1673[] {"texture", "type", "coords"};
    static constexpr const char *pnames1674[] {"texture", "type", "coords"};
    static constexpr const char *pnames1675[] {"texture", "type", "coords"};
    static constexpr const char *pnames1676[] {"texture", "type", "coords"};
    static constexpr const char *pnames1677[] {"texture", "type", "coords"};
    static constexpr const char *pnames1678[] {"texture", "type", "coords"};
    static constexpr const char *pnames1679[] {"texture", "type", "coords"};
    static constexpr const char *pnames1680[] {"texunit", "size", "type", "stride", "pointer"};
    static constexpr const char *pnames1681[] {"texunit", "target", "pname", "param"};
    static constexpr const char *pnames1682[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames1683[] {"texunit", "target", "pname", "param"};
    static constexpr const char *pnames1684[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames1685[] {"texunit", "coord", "pname", "param"};
    static constexpr const char *pnames1686[] {"texunit", "coord", "pname", "params"};
    static constexpr const char *pnames1687[] {"texunit", "coord", "pname", "param"};
    static constexpr const char *pnames1688[] {"texunit", "coord", "pname", "params"};
    static constexpr const char *pnames1689[] {"texunit", "coord", "pname", "param"};
    static constexpr const char *pnames1690[] {"texunit", "coord", "pname", "params"};
    static constexpr const char *pnames1691[] {"texunit", "target", "level", "internalformat", "width", "border", "format", "type", "pixels"};
    static constexpr const char *pnames1692[] {"texunit", "target", "level", "internalformat", "width", "height", "border", "format", "type", "pixels"};
    static constexpr const char *pnames1693[] {"texunit", "target", "level", "internalformat", "width", "height", "depth", "border", "format", "type", "pixels"};
    static constexpr const char *pnames1694[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames1695[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames1696[] {"texunit", "target", "pname", "param"};
    static constexpr const char *pnames1697[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames1698[] {"texunit", "target", "pname", "param"};
    static constexpr const char *pnames1699[] {"texunit", "target", "pname", "params"};
    static constexpr const char *pnames1700[] {"texunit", "target", "renderbuffer"};
    static constexpr const char *pnames1701[] {"texunit", "target", "level", "xoffset", "width", "format", "type", "pixels"};
    static constexpr const char *pnames1702[] {"texunit", "target", "level", "xoffset", "yoffset", "width", "height", "format", "type", "pixels"};
    static constexpr const char *pnames1703[] {"texunit", "target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "pixels"};
    static constexpr const char *pnames1704[] {"buffer", "size", "data", "usage"};
    static constexpr const char *pnames1705[] {"buffer", "size", "data", "usage"};
    static constexpr const char *pnames1706[] {"buffer", "offset", "size", "commit"};
    static constexpr const char *pnames1707[] {"buffer", "offset", "size", "commit"};
    static constexpr const char *pnames1708[] {"buffer", "size", "data", "flags"};
    static constexpr const char *pnames1709[] {"buffer", "size", "data", "flags"};
    static constexpr const char *pnames1710[] {"buffer", "offset", "size", "data"};
    static constexpr const char *pnames1711[] {"buffer", "offset", "size", "data"};
    static constexpr const char *pnames1712[] {"readBuffer", "writeBuffer", "readOffset", "writeOffset", "size"};
    static constexpr const char *pnames1713[] {"framebuffer", "buf"};
    static constexpr const char *pnames1714[] {"framebuffer", "n", "bufs"};
    static constexpr const char *pnames1715[] {"framebuffer", "pname", "param"};
    static constexpr const char *pnames1716[] {"framebuffer", "pname", "param"};
    static constexpr const char *pnames1717[] {"framebuffer", "src"};
    static constexpr const char *pnames1718[] {"framebuffer", "attachment", "renderbuffertarget", "renderbuffer"};
    static constexpr const char *pnames1719[] {"framebuffer", "attachment", "renderbuffertarget", "renderbuffer"};
    static constexpr const char *pnames1720[] {"framebuffer", "start", "count", "v"};
    static constexpr const char *pnames1721[] {"framebuffer", "start", "count", "v"};
    static constexpr const char *pnames1722[] {"framebuffer", "attachment", "texture", "level"};
    static constexpr const char *pnames1723[] {"framebuffer", "numsamples", "pixelindex", "values"};
    static constexpr const char *pnames1724[] {"framebuffer", "attachment", "textarget", "texture", "level"};
    static constexpr const char *pnames1725[] {"framebuffer", "attachment", "textarget", "texture", "level"};
    static constexpr const char *pnames1726[] {"framebuffer", "attachment", "textarget", "texture", "level", "zoffset"};
    static constexpr const char *pnames1727[] {"framebuffer", "attachment", "texture", "level"};
    static constexpr const char *pnames1728[] {"framebuffer", "attachment", "texture", "level", "face"};
    static constexpr const char *pnames1729[] {"framebuffer", "attachment", "texture", "level", "layer"};
    static constexpr const char *pnames1730[] {"framebuffer", "attachment", "texture", "level", "layer"};
    static constexpr const char *pnames1731[] {"program", "target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1732[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1733[] {"program", "target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1734[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1735[] {"program", "target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1736[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1737[] {"program", "target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1738[] {"program", "target", "index", "params"};
    static constexpr const char *pnames1739[] {"program", "target", "index", "count", "params"};
    static constexpr const char *pnames1740[] {"program", "target", "index", "count", "params"};
    static constexpr const char *pnames1741[] {"program", "target", "index", "count", "params"};
    static constexpr const char *pnames1742[] {"program", "target", "format", "len", "string"};
    static constexpr const char *pnames1743[] {"renderbuffer", "internalformat", "width", "height"};
    static constexpr const char *pnames1744[] {"renderbuffer", "internalformat", "width", "height"};
    static constexpr const char *pnames1745[] {"renderbuffer", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames1746[] {"renderbuffer", "coverageSamples", "colorSamples", "internalformat", "width", "height"};
    static constexpr const char *pnames1747[] {"renderbuffer", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames1748[] {"type", "namelen", "name", "stringlen", "string"};
    static constexpr const char *pnames1749[] {"list", "mode"};
    static constexpr const char *pnames1750[] {"size", "pointer", "usage"};
    static constexpr const char *pnames1751[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1752[] {"v"};
    static constexpr const char *pnames1753[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1754[] {"v"};
    static constexpr const char *pnames1755[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1756[] {"nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames1757[] {"n", "v"};
    static constexpr const char *pnames1758[] {"v"};
    static constexpr const char *pnames1759[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1760[] {"v"};
    static constexpr const char *pnames1761[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1762[] {"v"};
    static constexpr const char *pnames1763[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1764[] {"v"};
    static constexpr const char *pnames1765[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1766[] {"nx", "ny", "nz"};
    static constexpr const char *pnames1767[] {"coords"};
    static constexpr const char *pnames1768[] {"type", "stride"};
    static constexpr const char *pnames1769[] {"type", "coords"};
    static constexpr const char *pnames1770[] {"type", "coords"};
    static constexpr const char *pnames1771[] {"type", "stride", "pointer"};
    static constexpr const char *pnames1772[] {"type", "stride", "count", "pointer"};
    static constexpr const char *pnames1773[] {"type", "stride", "pointer", "ptrstride"};
    static constexpr const char *pnames1774[] {"type", "pointer"};
    static constexpr const char *pnames1775[] {"stream", "nx", "ny", "nz"};
    static constexpr const char *pnames1776[] {"stream", "coords"};
    static constexpr const char *pnames1777[] {"stream", "nx", "ny", "nz"};
    static constexpr const char *pnames1778[] {"stream", "coords"};
    static constexpr const char *pnames1779[] {"stream", "nx", "ny", "nz"};
    static constexpr const char *pnames1780[] {"stream", "coords"};
    static constexpr const char *pnames1781[] {"stream", "nx", "ny", "nz"};
    static constexpr const char *pnames1782[] {"stream", "coords"};
    static constexpr const char *pnames1783[] {"stream", "nx", "ny", "nz"};
    static constexpr const char *pnames1784[] {"stream", "coords"};
    static constexpr const char *pnames1785[] {"identifier", "name", "length", "label"};
    static constexpr const char *pnames1786[] {"identifier", "name", "length", "label"};
    static constexpr const char *pnames1787[] {"ptr", "length", "label"};
    static constexpr const char *pnames1788[] {"ptr", "length", "label"};
    static constexpr const char *pnames1789[] {"objectType", "name", "option"};
    static constexpr const char *pnames1790[] {"objectType", "name", "option"};
    static constexpr const char *pnames1791[] {"left", "right", "bottom", "top", "zNear", "zFar"};
    static constexpr const char *pnames1792[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames1793[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames1794[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames1795[] {"l", "r", "b", "t", "n", "f"};
    static constexpr const char *pnames1796[] {"pname", "param"};
    static constexpr const char *pnames1797[] {"pname", "param"};
    static constexpr const char *pnames1798[] {"dst", "coord", "swizzle"};
    static constexpr const char *pnames1799[] {"token"};
    static constexpr const char *pnames1800[] {"token"};
    static constexpr const char *pnames1801[] {"pname", "values"};
    static constexpr const char *pnames1802[] {"pname", "value"};
    static constexpr const char *pnames1803[] {"pname", "value"};
    static constexpr const char *pnames1804[] {"pname", "value"};
    static constexpr const char *pnames1805[] {"color", "genMode", "colorFormat", "coeffs"};
    static constexpr const char *pnames1806[] {"path", "numCommands", "commands", "numCoords", "coordType", "coords"};
    static constexpr const char *pnames1807[] {"path", "numCoords", "coordType", "coords"};
    static constexpr const char *pnames1808[] {"func"};
    static constexpr const char *pnames1809[] {"path", "dashCount", "dashArray"};
    static constexpr const char *pnames1810[] {"genMode"};
    static constexpr const char *pnames1811[] {"firstPathName", "fontTarget", "fontName", "fontStyle", "firstGlyphIndex", "numGlyphs", "pathParameterTemplate", "emScale"};
    static constexpr const char *pnames1812[] {"fontTarget", "fontName", "fontStyle", "pathParameterTemplate", "emScale", "baseAndCount"};
    static constexpr const char *pnames1813[] {"firstPathName", "fontTarget", "fontName", "fontStyle", "firstGlyph", "numGlyphs", "handleMissingGlyphs", "pathParameterTemplate", "emScale"};
    static constexpr const char *pnames1814[] {"firstPathName", "fontTarget", "fontName", "fontStyle", "numGlyphs", "type", "charcodes", "handleMissingGlyphs", "pathParameterTemplate", "emScale"};
    static constexpr const char *pnames1815[] {"firstPathName", "fontTarget", "fontSize", "fontData", "faceIndex", "firstGlyphIndex", "numGlyphs", "pathParameterTemplate", "emScale"};
    static constexpr const char *pnames1816[] {"path", "pname", "value"};
    static constexpr const char *pnames1817[] {"path", "pname", "value"};
    static constexpr const char *pnames1818[] {"path", "pname", "value"};
    static constexpr const char *pnames1819[] {"path", "pname", "value"};
    static constexpr const char *pnames1820[] {"factor", "units"};
    static constexpr const char *pnames1821[] {"func", "ref", "mask"};
    static constexpr const char *pnames1822[] {"path", "format", "length", "pathString"};
    static constexpr const char *pnames1823[] {"path", "commandStart", "commandsToDelete", "numCommands", "commands", "numCoords", "coordType", "coords"};
    static constexpr const char *pnames1824[] {"path", "coordStart", "numCoords", "coordType", "coords"};
    static constexpr const char *pnames1825[] {"texCoordSet", "genMode", "components", "coeffs"};
    static constexpr const char *pnames1826[] {""};
    static constexpr const char *pnames1827[] {""};
    static constexpr const char *pnames1828[] {"target", "length", "pointer"};
    static constexpr const char *pnames1829[] {"map", "mapsize", "values"};
    static constexpr const char *pnames1830[] {"map", "mapsize", "values"};
    static constexpr const char *pnames1831[] {"map", "mapsize", "values"};
    static constexpr const char *pnames1832[] {"map", "size", "values"};
    static constexpr const char *pnames1833[] {"pname", "param"};
    static constexpr const char *pnames1834[] {"pname", "param"};
    static constexpr const char *pnames1835[] {"pname", "param"};
    static constexpr const char *pnames1836[] {"pname", "param"};
    static constexpr const char *pnames1837[] {"pname", "params"};
    static constexpr const char *pnames1838[] {"pname", "param"};
    static constexpr const char *pnames1839[] {"pname", "params"};
    static constexpr const char *pnames1840[] {"mode"};
    static constexpr const char *pnames1841[] {"pname", "param"};
    static constexpr const char *pnames1842[] {"pname", "param"};
    static constexpr const char *pnames1843[] {"pname", "param"};
    static constexpr const char *pnames1844[] {"target", "pname", "param"};
    static constexpr const char *pnames1845[] {"target", "pname", "params"};
    static constexpr const char *pnames1846[] {"target", "pname", "param"};
    static constexpr const char *pnames1847[] {"target", "pname", "params"};
    static constexpr const char *pnames1848[] {"xfactor", "yfactor"};
    static constexpr const char *pnames1849[] {"xfactor", "yfactor"};
    static constexpr const char *pnames1850[] {"path", "startSegment", "numSegments", "distance", "x", "y", "tangentX", "tangentY"};
    static constexpr const char *pnames1851[] {"pname", "param"};
    static constexpr const char *pnames1852[] {"pname", "param"};
    static constexpr const char *pnames1853[] {"pname", "param"};
    static constexpr const char *pnames1854[] {"pname", "param"};
    static constexpr const char *pnames1855[] {"pname", "params"};
    static constexpr const char *pnames1856[] {"pname", "params"};
    static constexpr const char *pnames1857[] {"pname", "params"};
    static constexpr const char *pnames1858[] {"pname", "params"};
    static constexpr const char *pnames1859[] {"pname", "param"};
    static constexpr const char *pnames1860[] {"pname", "param"};
    static constexpr const char *pnames1861[] {"pname", "params"};
    static constexpr const char *pnames1862[] {"pname", "params"};
    static constexpr const char *pnames1863[] {"pname", "param"};
    static constexpr const char *pnames1864[] {"pname", "param"};
    static constexpr const char *pnames1865[] {"pname", "params"};
    static constexpr const char *pnames1866[] {"pname", "params"};
    static constexpr const char *pnames1867[] {"size"};
    static constexpr const char *pnames1868[] {"type", "stride", "pointer"};
    static constexpr const char *pnames1869[] {"size"};
    static constexpr const char *pnames1870[] {"size"};
    static constexpr const char *pnames1871[] {"markerp"};
    static constexpr const char *pnames1872[] {"marker_p"};
    static constexpr const char *pnames1873[] {"face", "mode"};
    static constexpr const char *pnames1874[] {"face", "mode"};
    static constexpr const char *pnames1875[] {"factor", "units"};
    static constexpr const char *pnames1876[] {"factor", "units", "clamp"};
    static constexpr const char *pnames1877[] {"factor", "bias"};
    static constexpr const char *pnames1878[] {"factor", "units"};
    static constexpr const char *pnames1879[] {"factor", "units"};
    static constexpr const char *pnames1880[] {"mask"};
    static constexpr const char *pnames1881[] {""};
    static constexpr const char *pnames1882[] {""};
    static constexpr const char *pnames1883[] {""};
    static constexpr const char *pnames1884[] {""};
    static constexpr const char *pnames1885[] {""};
    static constexpr const char *pnames1886[] {""};
    static constexpr const char *pnames1887[] {""};
    static constexpr const char *pnames1888[] {"video_slot", "minPresentTime", "beginPresentTimeId", "presentDurationId", "type", "target0", "fill0", "target1", "fill1", "target2", "fill2", "target3", "fill3"};
    static constexpr const char *pnames1889[] {"video_slot", "minPresentTime", "beginPresentTimeId", "presentDurationId", "type", "target0", "fill0", "key0", "target1", "fill1", "key1"};
    static constexpr const char *pnames1890[] {"minX", "minY", "minZ", "minW", "maxX", "maxY", "maxZ", "maxW"};
    static constexpr const char *pnames1891[] {"minX", "minY", "minZ", "minW", "maxX", "maxY", "maxZ", "maxW"};
    static constexpr const char *pnames1892[] {"minX", "minY", "minZ", "minW", "maxX", "maxY", "maxZ", "maxW"};
    static constexpr const char *pnames1893[] {"minX", "minY", "minZ", "minW", "maxX", "maxY", "maxZ", "maxW"};
    static constexpr const char *pnames1894[] {"index"};
    static constexpr const char *pnames1895[] {"index"};
    static constexpr const char *pnames1896[] {""};
    static constexpr const char *pnames1897[] {"n", "textures", "priorities"};
    static constexpr const char *pnames1898[] {"n", "textures", "priorities"};
    static constexpr const char *pnames1899[] {"n", "textures", "priorities"};
    static constexpr const char *pnames1900[] {"program", "binaryFormat", "binary", "length"};
    static constexpr const char *pnames1901[] {"program", "binaryFormat", "binary", "length"};
    static constexpr const char *pnames1902[] {"target", "bindingIndex", "wordIndex", "count", "params"};
    static constexpr const char *pnames1903[] {"target", "bindingIndex", "wordIndex", "count", "params"};
    static constexpr const char *pnames1904[] {"target", "bindingIndex", "wordIndex", "count", "params"};
    static constexpr const char *pnames1905[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1906[] {"target", "index", "params"};
    static constexpr const char *pnames1907[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1908[] {"target", "index", "params"};
    static constexpr const char *pnames1909[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1910[] {"target", "index", "params"};
    static constexpr const char *pnames1911[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1912[] {"target", "index", "params"};
    static constexpr const char *pnames1913[] {"target", "index", "count", "params"};
    static constexpr const char *pnames1914[] {"target", "index", "count", "params"};
    static constexpr const char *pnames1915[] {"target", "index", "count", "params"};
    static constexpr const char *pnames1916[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1917[] {"target", "index", "params"};
    static constexpr const char *pnames1918[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1919[] {"target", "index", "params"};
    static constexpr const char *pnames1920[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1921[] {"target", "index", "params"};
    static constexpr const char *pnames1922[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1923[] {"target", "index", "params"};
    static constexpr const char *pnames1924[] {"target", "index", "count", "params"};
    static constexpr const char *pnames1925[] {"target", "index", "count", "params"};
    static constexpr const char *pnames1926[] {"target", "index", "count", "params"};
    static constexpr const char *pnames1927[] {"id", "len", "name", "x", "y", "z", "w"};
    static constexpr const char *pnames1928[] {"id", "len", "name", "v"};
    static constexpr const char *pnames1929[] {"id", "len", "name", "x", "y", "z", "w"};
    static constexpr const char *pnames1930[] {"id", "len", "name", "v"};
    static constexpr const char *pnames1931[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1932[] {"target", "index", "v"};
    static constexpr const char *pnames1933[] {"target", "index", "x", "y", "z", "w"};
    static constexpr const char *pnames1934[] {"target", "index", "v"};
    static constexpr const char *pnames1935[] {"program", "pname", "value"};
    static constexpr const char *pnames1936[] {"program", "pname", "value"};
    static constexpr const char *pnames1937[] {"program", "pname", "value"};
    static constexpr const char *pnames1938[] {"target", "index", "count", "v"};
    static constexpr const char *pnames1939[] {"target", "index", "count", "v"};
    static constexpr const char *pnames1940[] {"program", "location", "genMode", "components", "coeffs"};
    static constexpr const char *pnames1941[] {"target", "format", "len", "string"};
    static constexpr const char *pnames1942[] {"target", "count", "params"};
    static constexpr const char *pnames1943[] {"program", "location", "v0"};
    static constexpr const char *pnames1944[] {"program", "location", "x"};
    static constexpr const char *pnames1945[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1946[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1947[] {"program", "location", "v0"};
    static constexpr const char *pnames1948[] {"program", "location", "v0"};
    static constexpr const char *pnames1949[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1950[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1951[] {"program", "location", "v0"};
    static constexpr const char *pnames1952[] {"program", "location", "x"};
    static constexpr const char *pnames1953[] {"program", "location", "x"};
    static constexpr const char *pnames1954[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1955[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1956[] {"program", "location", "v0"};
    static constexpr const char *pnames1957[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1958[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1959[] {"program", "location", "v0"};
    static constexpr const char *pnames1960[] {"program", "location", "x"};
    static constexpr const char *pnames1961[] {"program", "location", "x"};
    static constexpr const char *pnames1962[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1963[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1964[] {"program", "location", "v0"};
    static constexpr const char *pnames1965[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1966[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1967[] {"program", "location", "v0", "v1"};
    static constexpr const char *pnames1968[] {"program", "location", "x", "y"};
    static constexpr const char *pnames1969[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1970[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1971[] {"program", "location", "v0", "v1"};
    static constexpr const char *pnames1972[] {"program", "location", "v0", "v1"};
    static constexpr const char *pnames1973[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1974[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1975[] {"program", "location", "v0", "v1"};
    static constexpr const char *pnames1976[] {"program", "location", "x", "y"};
    static constexpr const char *pnames1977[] {"program", "location", "x", "y"};
    static constexpr const char *pnames1978[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1979[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1980[] {"program", "location", "v0", "v1"};
    static constexpr const char *pnames1981[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1982[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1983[] {"program", "location", "v0", "v1"};
    static constexpr const char *pnames1984[] {"program", "location", "x", "y"};
    static constexpr const char *pnames1985[] {"program", "location", "x", "y"};
    static constexpr const char *pnames1986[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1987[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1988[] {"program", "location", "v0", "v1"};
    static constexpr const char *pnames1989[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1990[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1991[] {"program", "location", "v0", "v1", "v2"};
    static constexpr const char *pnames1992[] {"program", "location", "x", "y", "z"};
    static constexpr const char *pnames1993[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1994[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1995[] {"program", "location", "v0", "v1", "v2"};
    static constexpr const char *pnames1996[] {"program", "location", "v0", "v1", "v2"};
    static constexpr const char *pnames1997[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1998[] {"program", "location", "count", "value"};
    static constexpr const char *pnames1999[] {"program", "location", "v0", "v1", "v2"};
    static constexpr const char *pnames2000[] {"program", "location", "x", "y", "z"};
    static constexpr const char *pnames2001[] {"program", "location", "x", "y", "z"};
    static constexpr const char *pnames2002[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2003[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2004[] {"program", "location", "v0", "v1", "v2"};
    static constexpr const char *pnames2005[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2006[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2007[] {"program", "location", "v0", "v1", "v2"};
    static constexpr const char *pnames2008[] {"program", "location", "x", "y", "z"};
    static constexpr const char *pnames2009[] {"program", "location", "x", "y", "z"};
    static constexpr const char *pnames2010[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2011[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2012[] {"program", "location", "v0", "v1", "v2"};
    static constexpr const char *pnames2013[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2014[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2015[] {"program", "location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2016[] {"program", "location", "x", "y", "z", "w"};
    static constexpr const char *pnames2017[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2018[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2019[] {"program", "location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2020[] {"program", "location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2021[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2022[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2023[] {"program", "location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2024[] {"program", "location", "x", "y", "z", "w"};
    static constexpr const char *pnames2025[] {"program", "location", "x", "y", "z", "w"};
    static constexpr const char *pnames2026[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2027[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2028[] {"program", "location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2029[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2030[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2031[] {"program", "location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2032[] {"program", "location", "x", "y", "z", "w"};
    static constexpr const char *pnames2033[] {"program", "location", "x", "y", "z", "w"};
    static constexpr const char *pnames2034[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2035[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2036[] {"program", "location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2037[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2038[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2039[] {"program", "location", "value"};
    static constexpr const char *pnames2040[] {"program", "location", "value"};
    static constexpr const char *pnames2041[] {"program", "location", "value"};
    static constexpr const char *pnames2042[] {"program", "location", "count", "values"};
    static constexpr const char *pnames2043[] {"program", "location", "count", "values"};
    static constexpr const char *pnames2044[] {"program", "location", "count", "values"};
    static constexpr const char *pnames2045[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2046[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2047[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2048[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2049[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2050[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2051[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2052[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2053[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2054[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2055[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2056[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2057[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2058[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2059[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2060[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2061[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2062[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2063[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2064[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2065[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2066[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2067[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2068[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2069[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2070[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2071[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2072[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2073[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2074[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2075[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2076[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2077[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2078[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2079[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2080[] {"program", "location", "count", "transpose", "value"};
    static constexpr const char *pnames2081[] {"program", "location", "value"};
    static constexpr const char *pnames2082[] {"program", "location", "count", "value"};
    static constexpr const char *pnames2083[] {"target", "limit"};
    static constexpr const char *pnames2084[] {"mode"};
    static constexpr const char *pnames2085[] {"mode"};
    static constexpr const char *pnames2086[] {"mask"};
    static constexpr const char *pnames2087[] {"mask"};
    static constexpr const char *pnames2088[] {"mask"};
    static constexpr const char *pnames2089[] {"source", "id", "length", "message"};
    static constexpr const char *pnames2090[] {"source", "id", "length", "message"};
    static constexpr const char *pnames2091[] {"length", "marker"};
    static constexpr const char *pnames2092[] {""};
    static constexpr const char *pnames2093[] {"name"};
    static constexpr const char *pnames2094[] {"id", "target"};
    static constexpr const char *pnames2095[] {"id", "target"};
    static constexpr const char *pnames2096[] {"mantissa", "exponent"};
    static constexpr const char *pnames2097[] {"target", "id", "pname", "param"};
    static constexpr const char *pnames2098[] {"x", "y"};
    static constexpr const char *pnames2099[] {"v"};
    static constexpr const char *pnames2100[] {"x", "y"};
    static constexpr const char *pnames2101[] {"v"};
    static constexpr const char *pnames2102[] {"x", "y"};
    static constexpr const char *pnames2103[] {"v"};
    static constexpr const char *pnames2104[] {"x", "y"};
    static constexpr const char *pnames2105[] {"v"};
    static constexpr const char *pnames2106[] {"x", "y"};
    static constexpr const char *pnames2107[] {"coords"};
    static constexpr const char *pnames2108[] {"x", "y", "z"};
    static constexpr const char *pnames2109[] {"v"};
    static constexpr const char *pnames2110[] {"x", "y", "z"};
    static constexpr const char *pnames2111[] {"v"};
    static constexpr const char *pnames2112[] {"x", "y", "z"};
    static constexpr const char *pnames2113[] {"v"};
    static constexpr const char *pnames2114[] {"x", "y", "z"};
    static constexpr const char *pnames2115[] {"v"};
    static constexpr const char *pnames2116[] {"x", "y", "z"};
    static constexpr const char *pnames2117[] {"coords"};
    static constexpr const char *pnames2118[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2119[] {"v"};
    static constexpr const char *pnames2120[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2121[] {"v"};
    static constexpr const char *pnames2122[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2123[] {"v"};
    static constexpr const char *pnames2124[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2125[] {"v"};
    static constexpr const char *pnames2126[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2127[] {"coords"};
    static constexpr const char *pnames2128[] {"samples", "fixedsamplelocations"};
    static constexpr const char *pnames2129[] {"src"};
    static constexpr const char *pnames2130[] {"src", "index"};
    static constexpr const char *pnames2131[] {"mode"};
    static constexpr const char *pnames2132[] {"marker"};
    static constexpr const char *pnames2133[] {"x", "y", "width", "height", "format", "type", "pixels"};
    static constexpr const char *pnames2134[] {"x", "y", "width", "height", "format", "type", "bufSize", "data"};
    static constexpr const char *pnames2135[] {"x", "y", "width", "height", "format", "type", "bufSize", "data"};
    static constexpr const char *pnames2136[] {"x", "y", "width", "height", "format", "type", "bufSize", "data"};
    static constexpr const char *pnames2137[] {"x", "y", "width", "height", "format", "type", "bufSize", "data"};
    static constexpr const char *pnames2138[] {"x1", "y1", "x2", "y2"};
    static constexpr const char *pnames2139[] {"v1", "v2"};
    static constexpr const char *pnames2140[] {"x1", "y1", "x2", "y2"};
    static constexpr const char *pnames2141[] {"v1", "v2"};
    static constexpr const char *pnames2142[] {"x1", "y1", "x2", "y2"};
    static constexpr const char *pnames2143[] {"v1", "v2"};
    static constexpr const char *pnames2144[] {"x1", "y1", "x2", "y2"};
    static constexpr const char *pnames2145[] {"v1", "v2"};
    static constexpr const char *pnames2146[] {"x1", "y1", "x2", "y2"};
    static constexpr const char *pnames2147[] {"v1", "v2"};
    static constexpr const char *pnames2148[] {"equation"};
    static constexpr const char *pnames2149[] {""};
    static constexpr const char *pnames2150[] {"mode"};
    static constexpr const char *pnames2151[] {"target", "internalformat", "width", "height"};
    static constexpr const char *pnames2152[] {"target", "internalformat", "width", "height"};
    static constexpr const char *pnames2153[] {"target", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames2154[] {"target", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames2155[] {"target", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames2156[] {"target", "coverageSamples", "colorSamples", "internalformat", "width", "height"};
    static constexpr const char *pnames2157[] {"target", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames2158[] {"target", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames2159[] {"target", "samples", "internalformat", "width", "height"};
    static constexpr const char *pnames2160[] {"target", "internalformat", "width", "height"};
    static constexpr const char *pnames2161[] {"type", "stride", "pointer"};
    static constexpr const char *pnames2162[] {"code"};
    static constexpr const char *pnames2163[] {"code"};
    static constexpr const char *pnames2164[] {"rc", "r", "g", "b", "x", "y", "z"};
    static constexpr const char *pnames2165[] {"rc", "c", "v"};
    static constexpr const char *pnames2166[] {"rc", "r", "g", "b", "a", "nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames2167[] {"rc", "c", "n", "v"};
    static constexpr const char *pnames2168[] {"rc", "r", "g", "b", "a", "x", "y", "z"};
    static constexpr const char *pnames2169[] {"rc", "c", "v"};
    static constexpr const char *pnames2170[] {"rc", "nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames2171[] {"rc", "n", "v"};
    static constexpr const char *pnames2172[] {"code"};
    static constexpr const char *pnames2173[] {"rc", "s", "t", "r", "g", "b", "a", "nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames2174[] {"rc", "tc", "c", "n", "v"};
    static constexpr const char *pnames2175[] {"rc", "s", "t", "nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames2176[] {"rc", "tc", "n", "v"};
    static constexpr const char *pnames2177[] {"rc", "s", "t", "x", "y", "z"};
    static constexpr const char *pnames2178[] {"rc", "tc", "v"};
    static constexpr const char *pnames2179[] {"rc", "x", "y", "z"};
    static constexpr const char *pnames2180[] {"rc", "v"};
    static constexpr const char *pnames2181[] {"code"};
    static constexpr const char *pnames2182[] {"code"};
    static constexpr const char *pnames2183[] {"code"};
    static constexpr const char *pnames2184[] {"n", "programs"};
    static constexpr const char *pnames2185[] {"target"};
    static constexpr const char *pnames2186[] {"target"};
    static constexpr const char *pnames2187[] {"target"};
    static constexpr const char *pnames2188[] {"target"};
    static constexpr const char *pnames2189[] {""};
    static constexpr const char *pnames2190[] {""};
    static constexpr const char *pnames2191[] {""};
    static constexpr const char *pnames2192[] {""};
    static constexpr const char *pnames2193[] {""};
    static constexpr const char *pnames2194[] {"angle", "x", "y", "z"};
    static constexpr const char *pnames2195[] {"angle", "x", "y", "z"};
    static constexpr const char *pnames2196[] {"angle", "x", "y", "z"};
    static constexpr const char *pnames2197[] {"angle", "x", "y", "z"};
    static constexpr const char *pnames2198[] {"value", "invert"};
    static constexpr const char *pnames2199[] {"value", "invert"};
    static constexpr const char *pnames2200[] {"value", "invert"};
    static constexpr const char *pnames2201[] {"value", "invert"};
    static constexpr const char *pnames2202[] {"dst", "interp", "swizzle"};
    static constexpr const char *pnames2203[] {"value", "invert"};
    static constexpr const char *pnames2204[] {"index", "mask"};
    static constexpr const char *pnames2205[] {"value", "invert"};
    static constexpr const char *pnames2206[] {"maskNumber", "mask"};
    static constexpr const char *pnames2207[] {"pattern"};
    static constexpr const char *pnames2208[] {"pattern"};
    static constexpr const char *pnames2209[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2210[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2211[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2212[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2213[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2214[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2215[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2216[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2217[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2218[] {"sampler", "pname", "param"};
    static constexpr const char *pnames2219[] {"x", "y", "z"};
    static constexpr const char *pnames2220[] {"x", "y", "z"};
    static constexpr const char *pnames2221[] {"x", "y", "z"};
    static constexpr const char *pnames2222[] {"x", "y", "z"};
    static constexpr const char *pnames2223[] {"x", "y", "width", "height"};
    static constexpr const char *pnames2224[] {"first", "count", "v"};
    static constexpr const char *pnames2225[] {"first", "count", "v"};
    static constexpr const char *pnames2226[] {"first", "count", "v"};
    static constexpr const char *pnames2227[] {"index", "left", "bottom", "width", "height"};
    static constexpr const char *pnames2228[] {"index", "left", "bottom", "width", "height"};
    static constexpr const char *pnames2229[] {"index", "left", "bottom", "width", "height"};
    static constexpr const char *pnames2230[] {"index", "v"};
    static constexpr const char *pnames2231[] {"index", "v"};
    static constexpr const char *pnames2232[] {"index", "v"};
    static constexpr const char *pnames2233[] {"red", "green", "blue"};
    static constexpr const char *pnames2234[] {"red", "green", "blue"};
    static constexpr const char *pnames2235[] {"v"};
    static constexpr const char *pnames2236[] {"v"};
    static constexpr const char *pnames2237[] {"red", "green", "blue"};
    static constexpr const char *pnames2238[] {"red", "green", "blue"};
    static constexpr const char *pnames2239[] {"v"};
    static constexpr const char *pnames2240[] {"v"};
    static constexpr const char *pnames2241[] {"red", "green", "blue"};
    static constexpr const char *pnames2242[] {"red", "green", "blue"};
    static constexpr const char *pnames2243[] {"v"};
    static constexpr const char *pnames2244[] {"v"};
    static constexpr const char *pnames2245[] {"red", "green", "blue"};
    static constexpr const char *pnames2246[] {"v"};
    static constexpr const char *pnames2247[] {"red", "green", "blue"};
    static constexpr const char *pnames2248[] {"red", "green", "blue"};
    static constexpr const char *pnames2249[] {"v"};
    static constexpr const char *pnames2250[] {"v"};
    static constexpr const char *pnames2251[] {"red", "green", "blue"};
    static constexpr const char *pnames2252[] {"red", "green", "blue"};
    static constexpr const char *pnames2253[] {"v"};
    static constexpr const char *pnames2254[] {"v"};
    static constexpr const char *pnames2255[] {"red", "green", "blue"};
    static constexpr const char *pnames2256[] {"red", "green", "blue"};
    static constexpr const char *pnames2257[] {"v"};
    static constexpr const char *pnames2258[] {"v"};
    static constexpr const char *pnames2259[] {"red", "green", "blue"};
    static constexpr const char *pnames2260[] {"red", "green", "blue"};
    static constexpr const char *pnames2261[] {"v"};
    static constexpr const char *pnames2262[] {"v"};
    static constexpr const char *pnames2263[] {"red", "green", "blue"};
    static constexpr const char *pnames2264[] {"red", "green", "blue"};
    static constexpr const char *pnames2265[] {"v"};
    static constexpr const char *pnames2266[] {"v"};
    static constexpr const char *pnames2267[] {"size", "type", "stride"};
    static constexpr const char *pnames2268[] {"type", "color"};
    static constexpr const char *pnames2269[] {"type", "color"};
    static constexpr const char *pnames2270[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames2271[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames2272[] {"size", "type", "stride", "pointer", "ptrstride"};
    static constexpr const char *pnames2273[] {"size", "buffer"};
    static constexpr const char *pnames2274[] {"monitor", "enable", "group", "numCounters", "counterList"};
    static constexpr const char *pnames2275[] {"target", "internalformat", "width", "height", "format", "type", "row", "column"};
    static constexpr const char *pnames2276[] {"target", "internalformat", "width", "height", "format", "type", "row", "column"};
    static constexpr const char *pnames2277[] {"fence"};
    static constexpr const char *pnames2278[] {"fence", "condition"};
    static constexpr const char *pnames2279[] {"dst", "value"};
    static constexpr const char *pnames2280[] {"id", "type", "addr"};
    static constexpr const char *pnames2281[] {"id", "type", "addr"};
    static constexpr const char *pnames2282[] {"pname", "index", "val"};
    static constexpr const char *pnames2283[] {"mode"};
    static constexpr const char *pnames2284[] {"count", "shaders", "binaryformat", "binary", "length"};
    static constexpr const char *pnames2285[] {"op", "res", "arg1"};
    static constexpr const char *pnames2286[] {"op", "res", "arg1", "arg2"};
    static constexpr const char *pnames2287[] {"op", "res", "arg1", "arg2", "arg3"};
    static constexpr const char *pnames2288[] {"shader", "count", "string", "length"};
    static constexpr const char *pnames2289[] {"shaderObj", "count", "string", "length"};
    static constexpr const char *pnames2290[] {"program", "storageBlockIndex", "storageBlockBinding"};
    static constexpr const char *pnames2291[] {"target", "n", "points"};
    static constexpr const char *pnames2292[] {"pname", "param"};
    static constexpr const char *pnames2293[] {"pname", "params"};
    static constexpr const char *pnames2294[] {"pname", "param"};
    static constexpr const char *pnames2295[] {"pname", "params"};
    static constexpr const char *pnames2296[] {""};
    static constexpr const char *pnames2297[] {"x", "y", "width", "height", "preserveMask"};
    static constexpr const char *pnames2298[] {"state", "mode"};
    static constexpr const char *pnames2299[] {"stencilTagBits", "stencilClearTag"};
    static constexpr const char *pnames2300[] {"numPaths", "pathNameType", "paths", "pathBase", "fillMode", "mask", "transformType", "transformValues"};
    static constexpr const char *pnames2301[] {"path", "fillMode", "mask"};
    static constexpr const char *pnames2302[] {"func", "ref", "mask"};
    static constexpr const char *pnames2303[] {"face", "func", "ref", "mask"};
    static constexpr const char *pnames2304[] {"frontfunc", "backfunc", "ref", "mask"};
    static constexpr const char *pnames2305[] {"mask"};
    static constexpr const char *pnames2306[] {"face", "mask"};
    static constexpr const char *pnames2307[] {"fail", "zfail", "zpass"};
    static constexpr const char *pnames2308[] {"face", "sfail", "dpfail", "dppass"};
    static constexpr const char *pnames2309[] {"face", "sfail", "dpfail", "dppass"};
    static constexpr const char *pnames2310[] {"face", "value"};
    static constexpr const char *pnames2311[] {"numPaths", "pathNameType", "paths", "pathBase", "reference", "mask", "transformType", "transformValues"};
    static constexpr const char *pnames2312[] {"path", "reference", "mask"};
    static constexpr const char *pnames2313[] {"numPaths", "pathNameType", "paths", "pathBase", "fillMode", "mask", "coverMode", "transformType", "transformValues"};
    static constexpr const char *pnames2314[] {"path", "fillMode", "mask", "coverMode"};
    static constexpr const char *pnames2315[] {"numPaths", "pathNameType", "paths", "pathBase", "reference", "mask", "coverMode", "transformType", "transformValues"};
    static constexpr const char *pnames2316[] {"path", "reference", "mask", "coverMode"};
    static constexpr const char *pnames2317[] {"marker"};
    static constexpr const char *pnames2318[] {"len", "string"};
    static constexpr const char *pnames2319[] {"xbits", "ybits"};
    static constexpr const char *pnames2320[] {"res", "in", "outX", "outY", "outZ", "outW"};
    static constexpr const char *pnames2321[] {"texture"};
    static constexpr const char *pnames2322[] {""};
    static constexpr const char *pnames2323[] {"tx", "ty", "tz"};
    static constexpr const char *pnames2324[] {"v"};
    static constexpr const char *pnames2325[] {"tx", "ty", "tz"};
    static constexpr const char *pnames2326[] {"v"};
    static constexpr const char *pnames2327[] {"tx", "ty", "tz"};
    static constexpr const char *pnames2328[] {"v"};
    static constexpr const char *pnames2329[] {"tx", "ty", "tz"};
    static constexpr const char *pnames2330[] {"v"};
    static constexpr const char *pnames2331[] {"tx", "ty", "tz"};
    static constexpr const char *pnames2332[] {"v"};
    static constexpr const char *pnames2333[] {"type", "stride", "pointer"};
    static constexpr const char *pnames2334[] {"mask"};
    static constexpr const char *pnames2335[] {"factor"};
    static constexpr const char *pnames2336[] {"mode"};
    static constexpr const char *pnames2337[] {"fence"};
    static constexpr const char *pnames2338[] {"fence"};
    static constexpr const char *pnames2339[] {"object", "name"};
    static constexpr const char *pnames2340[] {"target", "internalformat", "buffer"};
    static constexpr const char *pnames2341[] {"target", "internalformat", "buffer"};
    static constexpr const char *pnames2342[] {"target", "internalformat", "buffer"};
    static constexpr const char *pnames2343[] {"target", "internalformat", "buffer"};
    static constexpr const char *pnames2344[] {"target", "internalformat", "buffer", "offset", "size"};
    static constexpr const char *pnames2345[] {"target", "internalformat", "buffer", "offset", "size"};
    static constexpr const char *pnames2346[] {"target", "internalformat", "buffer", "offset", "size"};
    static constexpr const char *pnames2347[] {"pname", "param"};
    static constexpr const char *pnames2348[] {"pname", "param"};
    static constexpr const char *pnames2349[] {"s"};
    static constexpr const char *pnames2350[] {"coords"};
    static constexpr const char *pnames2351[] {"s"};
    static constexpr const char *pnames2352[] {"v"};
    static constexpr const char *pnames2353[] {"s"};
    static constexpr const char *pnames2354[] {"v"};
    static constexpr const char *pnames2355[] {"s"};
    static constexpr const char *pnames2356[] {"v"};
    static constexpr const char *pnames2357[] {"s"};
    static constexpr const char *pnames2358[] {"v"};
    static constexpr const char *pnames2359[] {"s"};
    static constexpr const char *pnames2360[] {"v"};
    static constexpr const char *pnames2361[] {"s"};
    static constexpr const char *pnames2362[] {"coords"};
    static constexpr const char *pnames2363[] {"s", "t"};
    static constexpr const char *pnames2364[] {"coords"};
    static constexpr const char *pnames2365[] {"s", "t"};
    static constexpr const char *pnames2366[] {"v"};
    static constexpr const char *pnames2367[] {"s", "t"};
    static constexpr const char *pnames2368[] {"s", "t", "r", "g", "b", "x", "y", "z"};
    static constexpr const char *pnames2369[] {"tc", "c", "v"};
    static constexpr const char *pnames2370[] {"s", "t", "r", "g", "b", "a", "nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames2371[] {"tc", "c", "n", "v"};
    static constexpr const char *pnames2372[] {"s", "t", "r", "g", "b", "a", "x", "y", "z"};
    static constexpr const char *pnames2373[] {"tc", "c", "v"};
    static constexpr const char *pnames2374[] {"s", "t", "nx", "ny", "nz", "x", "y", "z"};
    static constexpr const char *pnames2375[] {"tc", "n", "v"};
    static constexpr const char *pnames2376[] {"s", "t", "x", "y", "z"};
    static constexpr const char *pnames2377[] {"tc", "v"};
    static constexpr const char *pnames2378[] {"v"};
    static constexpr const char *pnames2379[] {"s", "t"};
    static constexpr const char *pnames2380[] {"v"};
    static constexpr const char *pnames2381[] {"s", "t"};
    static constexpr const char *pnames2382[] {"v"};
    static constexpr const char *pnames2383[] {"s", "t"};
    static constexpr const char *pnames2384[] {"v"};
    static constexpr const char *pnames2385[] {"s", "t"};
    static constexpr const char *pnames2386[] {"coords"};
    static constexpr const char *pnames2387[] {"s", "t", "r"};
    static constexpr const char *pnames2388[] {"coords"};
    static constexpr const char *pnames2389[] {"s", "t", "r"};
    static constexpr const char *pnames2390[] {"v"};
    static constexpr const char *pnames2391[] {"s", "t", "r"};
    static constexpr const char *pnames2392[] {"v"};
    static constexpr const char *pnames2393[] {"s", "t", "r"};
    static constexpr const char *pnames2394[] {"v"};
    static constexpr const char *pnames2395[] {"s", "t", "r"};
    static constexpr const char *pnames2396[] {"v"};
    static constexpr const char *pnames2397[] {"s", "t", "r"};
    static constexpr const char *pnames2398[] {"v"};
    static constexpr const char *pnames2399[] {"s", "t", "r"};
    static constexpr const char *pnames2400[] {"coords"};
    static constexpr const char *pnames2401[] {"s", "t", "r", "q"};
    static constexpr const char *pnames2402[] {"coords"};
    static constexpr const char *pnames2403[] {"s", "t", "r", "q"};
    static constexpr const char *pnames2404[] {"v"};
    static constexpr const char *pnames2405[] {"s", "t", "r", "q"};
    static constexpr const char *pnames2406[] {"s", "t", "p", "q", "r", "g", "b", "a", "nx", "ny", "nz", "x", "y", "z", "w"};
    static constexpr const char *pnames2407[] {"tc", "c", "n", "v"};
    static constexpr const char *pnames2408[] {"s", "t", "p", "q", "x", "y", "z", "w"};
    static constexpr const char *pnames2409[] {"tc", "v"};
    static constexpr const char *pnames2410[] {"v"};
    static constexpr const char *pnames2411[] {"s", "t", "r", "q"};
    static constexpr const char *pnames2412[] {"v"};
    static constexpr const char *pnames2413[] {"s", "t", "r", "q"};
    static constexpr const char *pnames2414[] {"v"};
    static constexpr const char *pnames2415[] {"s", "t", "r", "q"};
    static constexpr const char *pnames2416[] {"v"};
    static constexpr const char *pnames2417[] {"s", "t", "r", "q"};
    static constexpr const char *pnames2418[] {"coords"};
    static constexpr const char *pnames2419[] {"size", "type", "stride"};
    static constexpr const char *pnames2420[] {"type", "coords"};
    static constexpr const char *pnames2421[] {"type", "coords"};
    static constexpr const char *pnames2422[] {"type", "coords"};
    static constexpr const char *pnames2423[] {"type", "coords"};
    static constexpr const char *pnames2424[] {"type", "coords"};
    static constexpr const char *pnames2425[] {"type", "coords"};
    static constexpr const char *pnames2426[] {"type", "coords"};
    static constexpr const char *pnames2427[] {"type", "coords"};
    static constexpr const char *pnames2428[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames2429[] {"size", "type", "stride", "count", "pointer"};
    static constexpr const char *pnames2430[] {"size", "type", "stride", "pointer", "ptrstride"};
    static constexpr const char *pnames2431[] {"size", "type", "pointer"};
    static constexpr const char *pnames2432[] {"target", "pname", "param"};
    static constexpr const char *pnames2433[] {"target", "pname", "params"};
    static constexpr const char *pnames2434[] {"target", "pname", "param"};
    static constexpr const char *pnames2435[] {"target", "pname", "params"};
    static constexpr const char *pnames2436[] {"target", "pname", "param"};
    static constexpr const char *pnames2437[] {"target", "pname", "param"};
    static constexpr const char *pnames2438[] {"target", "pname", "params"};
    static constexpr const char *pnames2439[] {"target", "pname", "params"};
    static constexpr const char *pnames2440[] {"target", "filter", "n", "weights"};
    static constexpr const char *pnames2441[] {"coord", "pname", "param"};
    static constexpr const char *pnames2442[] {"coord", "pname", "params"};
    static constexpr const char *pnames2443[] {"coord", "pname", "param"};
    static constexpr const char *pnames2444[] {"coord", "pname", "param"};
    static constexpr const char *pnames2445[] {"coord", "pname", "params"};
    static constexpr const char *pnames2446[] {"coord", "pname", "params"};
    static constexpr const char *pnames2447[] {"coord", "pname", "param"};
    static constexpr const char *pnames2448[] {"coord", "pname", "param"};
    static constexpr const char *pnames2449[] {"coord", "pname", "params"};
    static constexpr const char *pnames2450[] {"coord", "pname", "params"};
    static constexpr const char *pnames2451[] {"coord", "pname", "param"};
    static constexpr const char *pnames2452[] {"coord", "pname", "params"};
    static constexpr const char *pnames2453[] {"target", "level", "internalformat", "width", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2454[] {"target", "level", "internalformat", "width", "height", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2455[] {"target", "samples", "internalformat", "width", "height", "fixedsamplelocations"};
    static constexpr const char *pnames2456[] {"target", "coverageSamples", "colorSamples", "internalFormat", "width", "height", "fixedSampleLocations"};
    static constexpr const char *pnames2457[] {"target", "level", "internalformat", "width", "height", "depth", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2458[] {"target", "level", "internalformat", "width", "height", "depth", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2459[] {"target", "samples", "internalformat", "width", "height", "depth", "fixedsamplelocations"};
    static constexpr const char *pnames2460[] {"target", "coverageSamples", "colorSamples", "internalFormat", "width", "height", "depth", "fixedSampleLocations"};
    static constexpr const char *pnames2461[] {"target", "level", "internalformat", "width", "height", "depth", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2462[] {"target", "level", "internalformat", "width", "height", "depth", "size4d", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2463[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "commit"};
    static constexpr const char *pnames2464[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "commit"};
    static constexpr const char *pnames2465[] {"target", "pname", "params"};
    static constexpr const char *pnames2466[] {"target", "pname", "params"};
    static constexpr const char *pnames2467[] {"target", "pname", "params"};
    static constexpr const char *pnames2468[] {"target", "pname", "params"};
    static constexpr const char *pnames2469[] {"target", "pname", "params"};
    static constexpr const char *pnames2470[] {"target", "pname", "params"};
    static constexpr const char *pnames2471[] {"target", "pname", "param"};
    static constexpr const char *pnames2472[] {"target", "pname", "params"};
    static constexpr const char *pnames2473[] {"target", "pname", "param"};
    static constexpr const char *pnames2474[] {"target", "pname", "params"};
    static constexpr const char *pnames2475[] {"target", "pname", "param"};
    static constexpr const char *pnames2476[] {"target", "pname", "param"};
    static constexpr const char *pnames2477[] {"target", "pname", "params"};
    static constexpr const char *pnames2478[] {"target", "pname", "params"};
    static constexpr const char *pnames2479[] {"target", "renderbuffer"};
    static constexpr const char *pnames2480[] {"target", "levels", "internalformat", "width"};
    static constexpr const char *pnames2481[] {"target", "levels", "internalformat", "width"};
    static constexpr const char *pnames2482[] {"target", "levels", "internalformat", "width", "height"};
    static constexpr const char *pnames2483[] {"target", "levels", "internalformat", "width", "height"};
    static constexpr const char *pnames2484[] {"target", "samples", "internalformat", "width", "height", "fixedsamplelocations"};
    static constexpr const char *pnames2485[] {"target", "levels", "internalformat", "width", "height", "depth"};
    static constexpr const char *pnames2486[] {"target", "levels", "internalformat", "width", "height", "depth"};
    static constexpr const char *pnames2487[] {"target", "samples", "internalformat", "width", "height", "depth", "fixedsamplelocations"};
    static constexpr const char *pnames2488[] {"target", "samples", "internalformat", "width", "height", "depth", "fixedsamplelocations"};
    static constexpr const char *pnames2489[] {"target", "internalFormat", "width", "height", "depth", "layers", "flags"};
    static constexpr const char *pnames2490[] {"target", "level", "xoffset", "width", "format", "type", "pixels"};
    static constexpr const char *pnames2491[] {"target", "level", "xoffset", "width", "format", "type", "pixels"};
    static constexpr const char *pnames2492[] {"target", "level", "xoffset", "yoffset", "width", "height", "format", "type", "pixels"};
    static constexpr const char *pnames2493[] {"target", "level", "xoffset", "yoffset", "width", "height", "format", "type", "pixels"};
    static constexpr const char *pnames2494[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "pixels"};
    static constexpr const char *pnames2495[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "pixels"};
    static constexpr const char *pnames2496[] {"target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "pixels"};
    static constexpr const char *pnames2497[] {"target", "level", "xoffset", "yoffset", "zoffset", "woffset", "width", "height", "depth", "size4d", "format", "type", "pixels"};
    static constexpr const char *pnames2498[] {""};
    static constexpr const char *pnames2499[] {""};
    static constexpr const char *pnames2500[] {"texture", "internalformat", "buffer"};
    static constexpr const char *pnames2501[] {"texture", "target", "internalformat", "buffer"};
    static constexpr const char *pnames2502[] {"texture", "internalformat", "buffer", "offset", "size"};
    static constexpr const char *pnames2503[] {"texture", "target", "internalformat", "buffer", "offset", "size"};
    static constexpr const char *pnames2504[] {"red", "green", "blue", "alpha"};
    static constexpr const char *pnames2505[] {"texture", "target", "level", "internalformat", "width", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2506[] {"texture", "target", "level", "internalformat", "width", "height", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2507[] {"texture", "target", "coverageSamples", "colorSamples", "internalFormat", "width", "height", "fixedSampleLocations"};
    static constexpr const char *pnames2508[] {"texture", "target", "samples", "internalFormat", "width", "height", "fixedSampleLocations"};
    static constexpr const char *pnames2509[] {"texture", "target", "level", "internalformat", "width", "height", "depth", "border", "format", "type", "pixels"};
    static constexpr const char *pnames2510[] {"texture", "target", "coverageSamples", "colorSamples", "internalFormat", "width", "height", "depth", "fixedSampleLocations"};
    static constexpr const char *pnames2511[] {"texture", "target", "samples", "internalFormat", "width", "height", "depth", "fixedSampleLocations"};
    static constexpr const char *pnames2512[] {"pname"};
    static constexpr const char *pnames2513[] {"face", "mode"};
    static constexpr const char *pnames2514[] {"mode"};
    static constexpr const char *pnames2515[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "commit"};
    static constexpr const char *pnames2516[] {"texture", "pname", "params"};
    static constexpr const char *pnames2517[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames2518[] {"texture", "pname", "params"};
    static constexpr const char *pnames2519[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames2520[] {"texture", "pname", "param"};
    static constexpr const char *pnames2521[] {"texture", "target", "pname", "param"};
    static constexpr const char *pnames2522[] {"texture", "pname", "param"};
    static constexpr const char *pnames2523[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames2524[] {"texture", "pname", "param"};
    static constexpr const char *pnames2525[] {"texture", "target", "pname", "param"};
    static constexpr const char *pnames2526[] {"texture", "pname", "param"};
    static constexpr const char *pnames2527[] {"texture", "target", "pname", "params"};
    static constexpr const char *pnames2528[] {"target", "length", "pointer"};
    static constexpr const char *pnames2529[] {"texture", "target", "renderbuffer"};
    static constexpr const char *pnames2530[] {"texture", "levels", "internalformat", "width"};
    static constexpr const char *pnames2531[] {"texture", "target", "levels", "internalformat", "width"};
    static constexpr const char *pnames2532[] {"texture", "levels", "internalformat", "width", "height"};
    static constexpr const char *pnames2533[] {"texture", "target", "levels", "internalformat", "width", "height"};
    static constexpr const char *pnames2534[] {"texture", "samples", "internalformat", "width", "height", "fixedsamplelocations"};
    static constexpr const char *pnames2535[] {"texture", "target", "samples", "internalformat", "width", "height", "fixedsamplelocations"};
    static constexpr const char *pnames2536[] {"texture", "levels", "internalformat", "width", "height", "depth"};
    static constexpr const char *pnames2537[] {"texture", "target", "levels", "internalformat", "width", "height", "depth"};
    static constexpr const char *pnames2538[] {"texture", "samples", "internalformat", "width", "height", "depth", "fixedsamplelocations"};
    static constexpr const char *pnames2539[] {"texture", "target", "samples", "internalformat", "width", "height", "depth", "fixedsamplelocations"};
    static constexpr const char *pnames2540[] {"texture", "target", "internalFormat", "width", "height", "depth", "layers", "flags"};
    static constexpr const char *pnames2541[] {"texture", "level", "xoffset", "width", "format", "type", "pixels"};
    static constexpr const char *pnames2542[] {"texture", "target", "level", "xoffset", "width", "format", "type", "pixels"};
    static constexpr const char *pnames2543[] {"texture", "level", "xoffset", "yoffset", "width", "height", "format", "type", "pixels"};
    static constexpr const char *pnames2544[] {"texture", "target", "level", "xoffset", "yoffset", "width", "height", "format", "type", "pixels"};
    static constexpr const char *pnames2545[] {"texture", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "pixels"};
    static constexpr const char *pnames2546[] {"texture", "target", "level", "xoffset", "yoffset", "zoffset", "width", "height", "depth", "format", "type", "pixels"};
    static constexpr const char *pnames2547[] {"texture", "target", "origtexture", "internalformat", "minlevel", "numlevels", "minlayer", "numlayers"};
    static constexpr const char *pnames2548[] {"texture", "target", "origtexture", "internalformat", "minlevel", "numlevels", "minlayer", "numlayers"};
    static constexpr const char *pnames2549[] {"texture", "target", "origtexture", "internalformat", "minlevel", "numlevels", "minlayer", "numlayers"};
    static constexpr const char *pnames2550[] {"target", "address", "matrix", "transform"};
    static constexpr const char *pnames2551[] {"count", "attribs", "bufferMode"};
    static constexpr const char *pnames2552[] {"xfb", "index", "buffer"};
    static constexpr const char *pnames2553[] {"xfb", "index", "buffer", "offset", "size"};
    static constexpr const char *pnames2554[] {"count", "attribs", "nbuffers", "bufstreams", "bufferMode"};
    static constexpr const char *pnames2555[] {"program", "count", "varyings", "bufferMode"};
    static constexpr const char *pnames2556[] {"program", "count", "varyings", "bufferMode"};
    static constexpr const char *pnames2557[] {"program", "count", "locations", "bufferMode"};
    static constexpr const char *pnames2558[] {"resultPath", "srcPath", "transformType", "transformValues"};
    static constexpr const char *pnames2559[] {"x", "y", "z"};
    static constexpr const char *pnames2560[] {"x", "y", "z"};
    static constexpr const char *pnames2561[] {"x", "y", "z"};
    static constexpr const char *pnames2562[] {"x", "y", "z"};
    static constexpr const char *pnames2563[] {"location", "x"};
    static constexpr const char *pnames2564[] {"location", "count", "value"};
    static constexpr const char *pnames2565[] {"location", "v0"};
    static constexpr const char *pnames2566[] {"location", "v0"};
    static constexpr const char *pnames2567[] {"location", "count", "value"};
    static constexpr const char *pnames2568[] {"location", "count", "value"};
    static constexpr const char *pnames2569[] {"location", "v0"};
    static constexpr const char *pnames2570[] {"location", "x"};
    static constexpr const char *pnames2571[] {"location", "x"};
    static constexpr const char *pnames2572[] {"location", "count", "value"};
    static constexpr const char *pnames2573[] {"location", "count", "value"};
    static constexpr const char *pnames2574[] {"location", "v0"};
    static constexpr const char *pnames2575[] {"location", "count", "value"};
    static constexpr const char *pnames2576[] {"location", "count", "value"};
    static constexpr const char *pnames2577[] {"location", "v0"};
    static constexpr const char *pnames2578[] {"location", "x"};
    static constexpr const char *pnames2579[] {"location", "x"};
    static constexpr const char *pnames2580[] {"location", "count", "value"};
    static constexpr const char *pnames2581[] {"location", "count", "value"};
    static constexpr const char *pnames2582[] {"location", "v0"};
    static constexpr const char *pnames2583[] {"location", "count", "value"};
    static constexpr const char *pnames2584[] {"location", "count", "value"};
    static constexpr const char *pnames2585[] {"location", "x", "y"};
    static constexpr const char *pnames2586[] {"location", "count", "value"};
    static constexpr const char *pnames2587[] {"location", "v0", "v1"};
    static constexpr const char *pnames2588[] {"location", "v0", "v1"};
    static constexpr const char *pnames2589[] {"location", "count", "value"};
    static constexpr const char *pnames2590[] {"location", "count", "value"};
    static constexpr const char *pnames2591[] {"location", "v0", "v1"};
    static constexpr const char *pnames2592[] {"location", "x", "y"};
    static constexpr const char *pnames2593[] {"location", "x", "y"};
    static constexpr const char *pnames2594[] {"location", "count", "value"};
    static constexpr const char *pnames2595[] {"location", "count", "value"};
    static constexpr const char *pnames2596[] {"location", "v0", "v1"};
    static constexpr const char *pnames2597[] {"location", "count", "value"};
    static constexpr const char *pnames2598[] {"location", "count", "value"};
    static constexpr const char *pnames2599[] {"location", "v0", "v1"};
    static constexpr const char *pnames2600[] {"location", "x", "y"};
    static constexpr const char *pnames2601[] {"location", "x", "y"};
    static constexpr const char *pnames2602[] {"location", "count", "value"};
    static constexpr const char *pnames2603[] {"location", "count", "value"};
    static constexpr const char *pnames2604[] {"location", "v0", "v1"};
    static constexpr const char *pnames2605[] {"location", "count", "value"};
    static constexpr const char *pnames2606[] {"location", "count", "value"};
    static constexpr const char *pnames2607[] {"location", "x", "y", "z"};
    static constexpr const char *pnames2608[] {"location", "count", "value"};
    static constexpr const char *pnames2609[] {"location", "v0", "v1", "v2"};
    static constexpr const char *pnames2610[] {"location", "v0", "v1", "v2"};
    static constexpr const char *pnames2611[] {"location", "count", "value"};
    static constexpr const char *pnames2612[] {"location", "count", "value"};
    static constexpr const char *pnames2613[] {"location", "v0", "v1", "v2"};
    static constexpr const char *pnames2614[] {"location", "x", "y", "z"};
    static constexpr const char *pnames2615[] {"location", "x", "y", "z"};
    static constexpr const char *pnames2616[] {"location", "count", "value"};
    static constexpr const char *pnames2617[] {"location", "count", "value"};
    static constexpr const char *pnames2618[] {"location", "v0", "v1", "v2"};
    static constexpr const char *pnames2619[] {"location", "count", "value"};
    static constexpr const char *pnames2620[] {"location", "count", "value"};
    static constexpr const char *pnames2621[] {"location", "v0", "v1", "v2"};
    static constexpr const char *pnames2622[] {"location", "x", "y", "z"};
    static constexpr const char *pnames2623[] {"location", "x", "y", "z"};
    static constexpr const char *pnames2624[] {"location", "count", "value"};
    static constexpr const char *pnames2625[] {"location", "count", "value"};
    static constexpr const char *pnames2626[] {"location", "v0", "v1", "v2"};
    static constexpr const char *pnames2627[] {"location", "count", "value"};
    static constexpr const char *pnames2628[] {"location", "count", "value"};
    static constexpr const char *pnames2629[] {"location", "x", "y", "z", "w"};
    static constexpr const char *pnames2630[] {"location", "count", "value"};
    static constexpr const char *pnames2631[] {"location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2632[] {"location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2633[] {"location", "count", "value"};
    static constexpr const char *pnames2634[] {"location", "count", "value"};
    static constexpr const char *pnames2635[] {"location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2636[] {"location", "x", "y", "z", "w"};
    static constexpr const char *pnames2637[] {"location", "x", "y", "z", "w"};
    static constexpr const char *pnames2638[] {"location", "count", "value"};
    static constexpr const char *pnames2639[] {"location", "count", "value"};
    static constexpr const char *pnames2640[] {"location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2641[] {"location", "count", "value"};
    static constexpr const char *pnames2642[] {"location", "count", "value"};
    static constexpr const char *pnames2643[] {"location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2644[] {"location", "x", "y", "z", "w"};
    static constexpr const char *pnames2645[] {"location", "x", "y", "z", "w"};
    static constexpr const char *pnames2646[] {"location", "count", "value"};
    static constexpr const char *pnames2647[] {"location", "count", "value"};
    static constexpr const char *pnames2648[] {"location", "v0", "v1", "v2", "v3"};
    static constexpr const char *pnames2649[] {"location", "count", "value"};
    static constexpr const char *pnames2650[] {"location", "count", "value"};
    static constexpr const char *pnames2651[] {"program", "uniformBlockIndex", "uniformBlockBinding"};
    static constexpr const char *pnames2652[] {"program", "location", "buffer"};
    static constexpr const char *pnames2653[] {"location", "value"};
    static constexpr const char *pnames2654[] {"location", "value"};
    static constexpr const char *pnames2655[] {"location", "value"};
    static constexpr const char *pnames2656[] {"location", "count", "value"};
    static constexpr const char *pnames2657[] {"location", "count", "value"};
    static constexpr const char *pnames2658[] {"location", "count", "value"};
    static constexpr const char *pnames2659[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2660[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2661[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2662[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2663[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2664[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2665[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2666[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2667[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2668[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2669[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2670[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2671[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2672[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2673[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2674[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2675[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2676[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2677[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2678[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2679[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2680[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2681[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2682[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2683[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2684[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2685[] {"location", "count", "transpose", "value"};
    static constexpr const char *pnames2686[] {"shadertype", "count", "indices"};
    static constexpr const char *pnames2687[] {"location", "value"};
    static constexpr const char *pnames2688[] {"location", "count", "value"};
    static constexpr const char *pnames2689[] {""};
    static constexpr const char *pnames2690[] {"target"};
    static constexpr const char *pnames2691[] {"target"};
    static constexpr const char *pnames2692[] {"target"};
    static constexpr const char *pnames2693[] {"buffer"};
    static constexpr const char *pnames2694[] {"buffer"};
    static constexpr const char *pnames2695[] {"buffer"};
    static constexpr const char *pnames2696[] {"texture", "level"};
    static constexpr const char *pnames2697[] {"buffer", "offset", "size", "pointer", "preserve"};
    static constexpr const char *pnames2698[] {"program"};
    static constexpr const char *pnames2699[] {"programObj"};
    static constexpr const char *pnames2700[] {"pipeline", "stages", "program"};
    static constexpr const char *pnames2701[] {"pipeline", "stages", "program"};
    static constexpr const char *pnames2702[] {"type", "program"};
    static constexpr const char *pnames2703[] {""};
    static constexpr const char *pnames2704[] {"surface", "pname", "bufSize", "length", "values"};
    static constexpr const char *pnames2705[] {"vdpDevice", "getProcAddress"};
    static constexpr const char *pnames2706[] {"surface"};
    static constexpr const char *pnames2707[] {"numSurfaces", "surfaces"};
    static constexpr const char *pnames2708[] {"vdpSurface", "target", "numTextureNames", "textureNames"};
    static constexpr const char *pnames2709[] {"vdpSurface", "target", "numTextureNames", "textureNames"};
    static constexpr const char *pnames2710[] {"surface", "access"};
    static constexpr const char *pnames2711[] {"numSurface", "surfaces"};
    static constexpr const char *pnames2712[] {"surface"};
    static constexpr const char *pnames2713[] {"program"};
    static constexpr const char *pnames2714[] {"programObj"};
    static constexpr const char *pnames2715[] {"pipeline"};
    static constexpr const char *pnames2716[] {"pipeline"};
    static constexpr const char *pnames2717[] {"id", "type", "stride", "buffer", "offset"};
    static constexpr const char *pnames2718[] {"id", "type", "stride", "addr"};
    static constexpr const char *pnames2719[] {"id", "addr"};
    static constexpr const char *pnames2720[] {"id", "addr"};
    static constexpr const char *pnames2721[] {"id", "addr"};
    static constexpr const char *pnames2722[] {"id", "addr"};
    static constexpr const char *pnames2723[] {"id", "addr"};
    static constexpr const char *pnames2724[] {"id", "addr"};
    static constexpr const char *pnames2725[] {"id", "addr"};
    static constexpr const char *pnames2726[] {"id", "addr"};
    static constexpr const char *pnames2727[] {"x", "y"};
    static constexpr const char *pnames2728[] {"coords"};
    static constexpr const char *pnames2729[] {"x", "y"};
    static constexpr const char *pnames2730[] {"v"};
    static constexpr const char *pnames2731[] {"x", "y"};
    static constexpr const char *pnames2732[] {"v"};
    static constexpr const char *pnames2733[] {"x", "y"};
    static constexpr const char *pnames2734[] {"v"};
    static constexpr const char *pnames2735[] {"x", "y"};
    static constexpr const char *pnames2736[] {"v"};
    static constexpr const char *pnames2737[] {"x", "y"};
    static constexpr const char *pnames2738[] {"v"};
    static constexpr const char *pnames2739[] {"x"};
    static constexpr const char *pnames2740[] {"coords"};
    static constexpr const char *pnames2741[] {"x", "y", "z"};
    static constexpr const char *pnames2742[] {"coords"};
    static constexpr const char *pnames2743[] {"x", "y", "z"};
    static constexpr const char *pnames2744[] {"v"};
    static constexpr const char *pnames2745[] {"x", "y", "z"};
    static constexpr const char *pnames2746[] {"v"};
    static constexpr const char *pnames2747[] {"x", "y", "z"};
    static constexpr const char *pnames2748[] {"v"};
    static constexpr const char *pnames2749[] {"x", "y", "z"};
    static constexpr const char *pnames2750[] {"v"};
    static constexpr const char *pnames2751[] {"x", "y", "z"};
    static constexpr const char *pnames2752[] {"v"};
    static constexpr const char *pnames2753[] {"x", "y"};
    static constexpr const char *pnames2754[] {"coords"};
    static constexpr const char *pnames2755[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2756[] {"coords"};
    static constexpr const char *pnames2757[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2758[] {"v"};
    static constexpr const char *pnames2759[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2760[] {"v"};
    static constexpr const char *pnames2761[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2762[] {"v"};
    static constexpr const char *pnames2763[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2764[] {"v"};
    static constexpr const char *pnames2765[] {"x", "y", "z", "w"};
    static constexpr const char *pnames2766[] {"v"};
    static constexpr const char *pnames2767[] {"x", "y", "z"};
    static constexpr const char *pnames2768[] {"coords"};
    static constexpr const char *pnames2769[] {"vaobj", "attribindex", "bindingindex"};
    static constexpr const char *pnames2770[] {"vaobj", "attribindex", "size", "type", "normalized", "relativeoffset"};
    static constexpr const char *pnames2771[] {"vaobj", "attribindex", "size", "type", "relativeoffset"};
    static constexpr const char *pnames2772[] {"vaobj", "attribindex", "size", "type", "relativeoffset"};
    static constexpr const char *pnames2773[] {"vaobj", "bindingindex", "buffer", "offset", "stride"};
    static constexpr const char *pnames2774[] {"vaobj", "bindingindex", "divisor"};
    static constexpr const char *pnames2775[] {"vaobj", "buffer", "size", "type", "stride", "offset"};
    static constexpr const char *pnames2776[] {"vaobj", "buffer", "stride", "offset"};
    static constexpr const char *pnames2777[] {"vaobj", "buffer"};
    static constexpr const char *pnames2778[] {"vaobj", "buffer", "type", "stride", "offset"};
    static constexpr const char *pnames2779[] {"vaobj", "buffer", "type", "stride", "offset"};
    static constexpr const char *pnames2780[] {"vaobj", "buffer", "texunit", "size", "type", "stride", "offset"};
    static constexpr const char *pnames2781[] {"vaobj", "buffer", "type", "stride", "offset"};
    static constexpr const char *pnames2782[] {"pname", "param"};
    static constexpr const char *pnames2783[] {"length", "pointer"};
    static constexpr const char *pnames2784[] {"length", "pointer"};
    static constexpr const char *pnames2785[] {"vaobj", "buffer", "size", "type", "stride", "offset"};
    static constexpr const char *pnames2786[] {"vaobj", "buffer", "size", "type", "stride", "offset"};
    static constexpr const char *pnames2787[] {"vaobj", "attribindex", "bindingindex"};
    static constexpr const char *pnames2788[] {"vaobj", "index", "divisor"};
    static constexpr const char *pnames2789[] {"vaobj", "attribindex", "size", "type", "normalized", "relativeoffset"};
    static constexpr const char *pnames2790[] {"vaobj", "attribindex", "size", "type", "relativeoffset"};
    static constexpr const char *pnames2791[] {"vaobj", "buffer", "index", "size", "type", "stride", "offset"};
    static constexpr const char *pnames2792[] {"vaobj", "attribindex", "size", "type", "relativeoffset"};
    static constexpr const char *pnames2793[] {"vaobj", "buffer", "index", "size", "type", "stride", "offset"};
    static constexpr const char *pnames2794[] {"vaobj", "buffer", "index", "size", "type", "normalized", "stride", "offset"};
    static constexpr const char *pnames2795[] {"vaobj", "bindingindex", "divisor"};
    static constexpr const char *pnames2796[] {"vaobj", "bindingindex", "buffer", "offset", "stride"};
    static constexpr const char *pnames2797[] {"vaobj", "first", "count", "buffers", "offsets", "strides"};
    static constexpr const char *pnames2798[] {"vaobj", "buffer", "size", "type", "stride", "offset"};
    static constexpr const char *pnames2799[] {"index", "x"};
    static constexpr const char *pnames2800[] {"index", "x"};
    static constexpr const char *pnames2801[] {"index", "x"};
    static constexpr const char *pnames2802[] {"index", "v"};
    static constexpr const char *pnames2803[] {"index", "v"};
    static constexpr const char *pnames2804[] {"index", "v"};
    static constexpr const char *pnames2805[] {"index", "x"};
    static constexpr const char *pnames2806[] {"index", "x"};
    static constexpr const char *pnames2807[] {"index", "x"};
    static constexpr const char *pnames2808[] {"index", "v"};
    static constexpr const char *pnames2809[] {"index", "v"};
    static constexpr const char *pnames2810[] {"index", "v"};
    static constexpr const char *pnames2811[] {"index", "x"};
    static constexpr const char *pnames2812[] {"index", "v"};
    static constexpr const char *pnames2813[] {"index", "x"};
    static constexpr const char *pnames2814[] {"index", "x"};
    static constexpr const char *pnames2815[] {"index", "x"};
    static constexpr const char *pnames2816[] {"index", "v"};
    static constexpr const char *pnames2817[] {"index", "v"};
    static constexpr const char *pnames2818[] {"index", "v"};
    static constexpr const char *pnames2819[] {"index", "x", "y"};
    static constexpr const char *pnames2820[] {"index", "x", "y"};
    static constexpr const char *pnames2821[] {"index", "x", "y"};
    static constexpr const char *pnames2822[] {"index", "v"};
    static constexpr const char *pnames2823[] {"index", "v"};
    static constexpr const char *pnames2824[] {"index", "v"};
    static constexpr const char *pnames2825[] {"index", "x", "y"};
    static constexpr const char *pnames2826[] {"index", "x", "y"};
    static constexpr const char *pnames2827[] {"index", "x", "y"};
    static constexpr const char *pnames2828[] {"index", "v"};
    static constexpr const char *pnames2829[] {"index", "v"};
    static constexpr const char *pnames2830[] {"index", "v"};
    static constexpr const char *pnames2831[] {"index", "x", "y"};
    static constexpr const char *pnames2832[] {"index", "v"};
    static constexpr const char *pnames2833[] {"index", "x", "y"};
    static constexpr const char *pnames2834[] {"index", "x", "y"};
    static constexpr const char *pnames2835[] {"index", "x", "y"};
    static constexpr const char *pnames2836[] {"index", "v"};
    static constexpr const char *pnames2837[] {"index", "v"};
    static constexpr const char *pnames2838[] {"index", "v"};
    static constexpr const char *pnames2839[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2840[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2841[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2842[] {"index", "v"};
    static constexpr const char *pnames2843[] {"index", "v"};
    static constexpr const char *pnames2844[] {"index", "v"};
    static constexpr const char *pnames2845[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2846[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2847[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2848[] {"index", "v"};
    static constexpr const char *pnames2849[] {"index", "v"};
    static constexpr const char *pnames2850[] {"index", "v"};
    static constexpr const char *pnames2851[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2852[] {"index", "v"};
    static constexpr const char *pnames2853[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2854[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2855[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2856[] {"index", "v"};
    static constexpr const char *pnames2857[] {"index", "v"};
    static constexpr const char *pnames2858[] {"index", "v"};
    static constexpr const char *pnames2859[] {"index", "v"};
    static constexpr const char *pnames2860[] {"index", "v"};
    static constexpr const char *pnames2861[] {"index", "v"};
    static constexpr const char *pnames2862[] {"index", "v"};
    static constexpr const char *pnames2863[] {"index", "v"};
    static constexpr const char *pnames2864[] {"index", "v"};
    static constexpr const char *pnames2865[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2866[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2867[] {"index", "v"};
    static constexpr const char *pnames2868[] {"index", "v"};
    static constexpr const char *pnames2869[] {"index", "v"};
    static constexpr const char *pnames2870[] {"index", "v"};
    static constexpr const char *pnames2871[] {"index", "v"};
    static constexpr const char *pnames2872[] {"index", "v"};
    static constexpr const char *pnames2873[] {"index", "v"};
    static constexpr const char *pnames2874[] {"index", "v"};
    static constexpr const char *pnames2875[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2876[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2877[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2878[] {"index", "v"};
    static constexpr const char *pnames2879[] {"index", "v"};
    static constexpr const char *pnames2880[] {"index", "v"};
    static constexpr const char *pnames2881[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2882[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2883[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2884[] {"index", "v"};
    static constexpr const char *pnames2885[] {"index", "v"};
    static constexpr const char *pnames2886[] {"index", "v"};
    static constexpr const char *pnames2887[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2888[] {"index", "v"};
    static constexpr const char *pnames2889[] {"index", "v"};
    static constexpr const char *pnames2890[] {"index", "v"};
    static constexpr const char *pnames2891[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2892[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2893[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2894[] {"index", "v"};
    static constexpr const char *pnames2895[] {"index", "v"};
    static constexpr const char *pnames2896[] {"index", "v"};
    static constexpr const char *pnames2897[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2898[] {"index", "v"};
    static constexpr const char *pnames2899[] {"index", "v"};
    static constexpr const char *pnames2900[] {"index", "v"};
    static constexpr const char *pnames2901[] {"index", "v"};
    static constexpr const char *pnames2902[] {"index", "v"};
    static constexpr const char *pnames2903[] {"index", "v"};
    static constexpr const char *pnames2904[] {"index", "v"};
    static constexpr const char *pnames2905[] {"index", "size", "type", "normalized", "stride", "buffer", "offset"};
    static constexpr const char *pnames2906[] {"attribindex", "bindingindex"};
    static constexpr const char *pnames2907[] {"index", "divisor"};
    static constexpr const char *pnames2908[] {"index", "divisor"};
    static constexpr const char *pnames2909[] {"index", "divisor"};
    static constexpr const char *pnames2910[] {"index", "divisor"};
    static constexpr const char *pnames2911[] {"index", "divisor"};
    static constexpr const char *pnames2912[] {"attribindex", "size", "type", "normalized", "relativeoffset"};
    static constexpr const char *pnames2913[] {"index", "size", "type", "normalized", "stride"};
    static constexpr const char *pnames2914[] {"index", "x"};
    static constexpr const char *pnames2915[] {"index", "x"};
    static constexpr const char *pnames2916[] {"index", "v"};
    static constexpr const char *pnames2917[] {"index", "v"};
    static constexpr const char *pnames2918[] {"index", "x"};
    static constexpr const char *pnames2919[] {"index", "x"};
    static constexpr const char *pnames2920[] {"index", "v"};
    static constexpr const char *pnames2921[] {"index", "v"};
    static constexpr const char *pnames2922[] {"index", "x", "y"};
    static constexpr const char *pnames2923[] {"index", "x", "y"};
    static constexpr const char *pnames2924[] {"index", "v"};
    static constexpr const char *pnames2925[] {"index", "v"};
    static constexpr const char *pnames2926[] {"index", "x", "y"};
    static constexpr const char *pnames2927[] {"index", "x", "y"};
    static constexpr const char *pnames2928[] {"index", "v"};
    static constexpr const char *pnames2929[] {"index", "v"};
    static constexpr const char *pnames2930[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2931[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2932[] {"index", "v"};
    static constexpr const char *pnames2933[] {"index", "v"};
    static constexpr const char *pnames2934[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2935[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2936[] {"index", "v"};
    static constexpr const char *pnames2937[] {"index", "v"};
    static constexpr const char *pnames2938[] {"index", "v"};
    static constexpr const char *pnames2939[] {"index", "v"};
    static constexpr const char *pnames2940[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2941[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2942[] {"index", "v"};
    static constexpr const char *pnames2943[] {"index", "v"};
    static constexpr const char *pnames2944[] {"index", "v"};
    static constexpr const char *pnames2945[] {"index", "v"};
    static constexpr const char *pnames2946[] {"index", "v"};
    static constexpr const char *pnames2947[] {"index", "v"};
    static constexpr const char *pnames2948[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2949[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2950[] {"index", "v"};
    static constexpr const char *pnames2951[] {"index", "v"};
    static constexpr const char *pnames2952[] {"index", "v"};
    static constexpr const char *pnames2953[] {"index", "v"};
    static constexpr const char *pnames2954[] {"attribindex", "size", "type", "relativeoffset"};
    static constexpr const char *pnames2955[] {"index", "size", "type", "stride"};
    static constexpr const char *pnames2956[] {"index", "size", "type", "stride", "pointer"};
    static constexpr const char *pnames2957[] {"index", "size", "type", "stride", "pointer"};
    static constexpr const char *pnames2958[] {"index", "x"};
    static constexpr const char *pnames2959[] {"index", "x"};
    static constexpr const char *pnames2960[] {"index", "v"};
    static constexpr const char *pnames2961[] {"index", "v"};
    static constexpr const char *pnames2962[] {"index", "x"};
    static constexpr const char *pnames2963[] {"index", "v"};
    static constexpr const char *pnames2964[] {"index", "x"};
    static constexpr const char *pnames2965[] {"index", "x"};
    static constexpr const char *pnames2966[] {"index", "v"};
    static constexpr const char *pnames2967[] {"index", "v"};
    static constexpr const char *pnames2968[] {"index", "x", "y"};
    static constexpr const char *pnames2969[] {"index", "x", "y"};
    static constexpr const char *pnames2970[] {"index", "v"};
    static constexpr const char *pnames2971[] {"index", "v"};
    static constexpr const char *pnames2972[] {"index", "x", "y"};
    static constexpr const char *pnames2973[] {"index", "v"};
    static constexpr const char *pnames2974[] {"index", "x", "y"};
    static constexpr const char *pnames2975[] {"index", "v"};
    static constexpr const char *pnames2976[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2977[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2978[] {"index", "v"};
    static constexpr const char *pnames2979[] {"index", "v"};
    static constexpr const char *pnames2980[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2981[] {"index", "v"};
    static constexpr const char *pnames2982[] {"index", "x", "y", "z"};
    static constexpr const char *pnames2983[] {"index", "v"};
    static constexpr const char *pnames2984[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2985[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2986[] {"index", "v"};
    static constexpr const char *pnames2987[] {"index", "v"};
    static constexpr const char *pnames2988[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2989[] {"index", "v"};
    static constexpr const char *pnames2990[] {"index", "x", "y", "z", "w"};
    static constexpr const char *pnames2991[] {"index", "v"};
    static constexpr const char *pnames2992[] {"attribindex", "size", "type", "relativeoffset"};
    static constexpr const char *pnames2993[] {"index", "size", "type", "stride"};
    static constexpr const char *pnames2994[] {"index", "size", "type", "stride", "pointer"};
    static constexpr const char *pnames2995[] {"index", "size", "type", "stride", "pointer"};
    static constexpr const char *pnames2996[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames2997[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames2998[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames2999[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames3000[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames3001[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames3002[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames3003[] {"index", "type", "normalized", "value"};
    static constexpr const char *pnames3004[] {"index", "pname", "param"};
    static constexpr const char *pnames3005[] {"index", "size", "type", "normalized", "stride", "pointer"};
    static constexpr const char *pnames3006[] {"index", "size", "type", "normalized", "stride", "pointer"};
    static constexpr const char *pnames3007[] {"index", "fsize", "type", "stride", "pointer"};
    static constexpr const char *pnames3008[] {"index", "count", "v"};
    static constexpr const char *pnames3009[] {"index", "count", "v"};
    static constexpr const char *pnames3010[] {"index", "n", "v"};
    static constexpr const char *pnames3011[] {"index", "count", "v"};
    static constexpr const char *pnames3012[] {"index", "count", "v"};
    static constexpr const char *pnames3013[] {"index", "count", "v"};
    static constexpr const char *pnames3014[] {"index", "n", "v"};
    static constexpr const char *pnames3015[] {"index", "count", "v"};
    static constexpr const char *pnames3016[] {"index", "count", "v"};
    static constexpr const char *pnames3017[] {"index", "count", "v"};
    static constexpr const char *pnames3018[] {"index", "n", "v"};
    static constexpr const char *pnames3019[] {"index", "count", "v"};
    static constexpr const char *pnames3020[] {"index", "count", "v"};
    static constexpr const char *pnames3021[] {"index", "count", "v"};
    static constexpr const char *pnames3022[] {"index", "n", "v"};
    static constexpr const char *pnames3023[] {"index", "count", "v"};
    static constexpr const char *pnames3024[] {"index", "count", "v"};
    static constexpr const char *pnames3025[] {"bindingindex", "divisor"};
    static constexpr const char *pnames3026[] {"count"};
    static constexpr const char *pnames3027[] {"pname", "param"};
    static constexpr const char *pnames3028[] {"pname", "param"};
    static constexpr const char *pnames3029[] {"size", "type", "stride"};
    static constexpr const char *pnames3030[] {"type", "value"};
    static constexpr const char *pnames3031[] {"type", "value"};
    static constexpr const char *pnames3032[] {"type", "value"};
    static constexpr const char *pnames3033[] {"type", "value"};
    static constexpr const char *pnames3034[] {"type", "value"};
    static constexpr const char *pnames3035[] {"type", "value"};
    static constexpr const char *pnames3036[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames3037[] {"size", "type", "stride", "count", "pointer"};
    static constexpr const char *pnames3038[] {"size", "type", "stride", "pointer", "ptrstride"};
    static constexpr const char *pnames3039[] {"size", "type", "pointer"};
    static constexpr const char *pnames3040[] {"stream", "x"};
    static constexpr const char *pnames3041[] {"stream", "coords"};
    static constexpr const char *pnames3042[] {"stream", "x"};
    static constexpr const char *pnames3043[] {"stream", "coords"};
    static constexpr const char *pnames3044[] {"stream", "x"};
    static constexpr const char *pnames3045[] {"stream", "coords"};
    static constexpr const char *pnames3046[] {"stream", "x"};
    static constexpr const char *pnames3047[] {"stream", "coords"};
    static constexpr const char *pnames3048[] {"stream", "x", "y"};
    static constexpr const char *pnames3049[] {"stream", "coords"};
    static constexpr const char *pnames3050[] {"stream", "x", "y"};
    static constexpr const char *pnames3051[] {"stream", "coords"};
    static constexpr const char *pnames3052[] {"stream", "x", "y"};
    static constexpr const char *pnames3053[] {"stream", "coords"};
    static constexpr const char *pnames3054[] {"stream", "x", "y"};
    static constexpr const char *pnames3055[] {"stream", "coords"};
    static constexpr const char *pnames3056[] {"stream", "x", "y", "z"};
    static constexpr const char *pnames3057[] {"stream", "coords"};
    static constexpr const char *pnames3058[] {"stream", "x", "y", "z"};
    static constexpr const char *pnames3059[] {"stream", "coords"};
    static constexpr const char *pnames3060[] {"stream", "x", "y", "z"};
    static constexpr const char *pnames3061[] {"stream", "coords"};
    static constexpr const char *pnames3062[] {"stream", "x", "y", "z"};
    static constexpr const char *pnames3063[] {"stream", "coords"};
    static constexpr const char *pnames3064[] {"stream", "x", "y", "z", "w"};
    static constexpr const char *pnames3065[] {"stream", "coords"};
    static constexpr const char *pnames3066[] {"stream", "x", "y", "z", "w"};
    static constexpr const char *pnames3067[] {"stream", "coords"};
    static constexpr const char *pnames3068[] {"stream", "x", "y", "z", "w"};
    static constexpr const char *pnames3069[] {"stream", "coords"};
    static constexpr const char *pnames3070[] {"stream", "x", "y", "z", "w"};
    static constexpr const char *pnames3071[] {"stream", "coords"};
    static constexpr const char *pnames3072[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames3073[] {"weight"};
    static constexpr const char *pnames3074[] {"weight"};
    static constexpr const char *pnames3075[] {"weight"};
    static constexpr const char *pnames3076[] {"weight"};
    static constexpr const char *pnames3077[] {"video_capture_slot", "sequence_num", "capture_time"};
    static constexpr const char *pnames3078[] {"video_capture_slot", "stream", "pname", "params"};
    static constexpr const char *pnames3079[] {"video_capture_slot", "stream", "pname", "params"};
    static constexpr const char *pnames3080[] {"video_capture_slot", "stream", "pname", "params"};
    static constexpr const char *pnames3081[] {"x", "y", "width", "height"};
    static constexpr const char *pnames3082[] {"first", "count", "v"};
    static constexpr const char *pnames3083[] {"first", "count", "v"};
    static constexpr const char *pnames3084[] {"first", "count", "v"};
    static constexpr const char *pnames3085[] {"index", "x", "y", "w", "h"};
    static constexpr const char *pnames3086[] {"index", "x", "y", "w", "h"};
    static constexpr const char *pnames3087[] {"index", "x", "y", "w", "h"};
    static constexpr const char *pnames3088[] {"index", "v"};
    static constexpr const char *pnames3089[] {"index", "v"};
    static constexpr const char *pnames3090[] {"index", "v"};
    static constexpr const char *pnames3091[] {"index", "xcoeff", "ycoeff"};
    static constexpr const char *pnames3092[] {"index", "swizzlex", "swizzley", "swizzlez", "swizzlew"};
    static constexpr const char *pnames3093[] {"sync", "flags", "timeout"};
    static constexpr const char *pnames3094[] {"sync", "flags", "timeout"};
    static constexpr const char *pnames3095[] {"resultPath", "numPaths", "paths", "weights"};
    static constexpr const char *pnames3096[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames3097[] {"size", "type", "stride", "pointer"};
    static constexpr const char *pnames3098[] {"size", "weights"};
    static constexpr const char *pnames3099[] {"size", "weights"};
    static constexpr const char *pnames3100[] {"size", "weights"};
    static constexpr const char *pnames3101[] {"size", "weights"};
    static constexpr const char *pnames3102[] {"size", "weights"};
    static constexpr const char *pnames3103[] {"size", "weights"};
    static constexpr const char *pnames3104[] {"size", "weights"};
    static constexpr const char *pnames3105[] {"size", "weights"};
    static constexpr const char *pnames3106[] {"x", "y"};
    static constexpr const char *pnames3107[] {"x", "y"};
    static constexpr const char *pnames3108[] {"x", "y"};
    static constexpr const char *pnames3109[] {"v"};
    static constexpr const char *pnames3110[] {"v"};
    static constexpr const char *pnames3111[] {"v"};
    static constexpr const char *pnames3112[] {"x", "y"};
    static constexpr const char *pnames3113[] {"x", "y"};
    static constexpr const char *pnames3114[] {"x", "y"};
    static constexpr const char *pnames3115[] {"v"};
    static constexpr const char *pnames3116[] {"v"};
    static constexpr const char *pnames3117[] {"v"};
    static constexpr const char *pnames3118[] {"x", "y"};
    static constexpr const char *pnames3119[] {"x", "y"};
    static constexpr const char *pnames3120[] {"x", "y"};
    static constexpr const char *pnames3121[] {"v"};
    static constexpr const char *pnames3122[] {"v"};
    static constexpr const char *pnames3123[] {"v"};
    static constexpr const char *pnames3124[] {"x", "y"};
    static constexpr const char *pnames3125[] {"x", "y"};
    static constexpr const char *pnames3126[] {"x", "y"};
    static constexpr const char *pnames3127[] {"v"};
    static constexpr const char *pnames3128[] {"v"};
    static constexpr const char *pnames3129[] {"v"};
    static constexpr const char *pnames3130[] {"x", "y", "z"};
    static constexpr const char *pnames3131[] {"x", "y", "z"};
    static constexpr const char *pnames3132[] {"x", "y", "z"};
    static constexpr const char *pnames3133[] {"v"};
    static constexpr const char *pnames3134[] {"v"};
    static constexpr const char *pnames3135[] {"v"};
    static constexpr const char *pnames3136[] {"x", "y", "z"};
    static constexpr const char *pnames3137[] {"x", "y", "z"};
    static constexpr const char *pnames3138[] {"x", "y", "z"};
    static constexpr const char *pnames3139[] {"v"};
    static constexpr const char *pnames3140[] {"v"};
    static constexpr const char *pnames3141[] {"v"};
    static constexpr const char *pnames3142[] {"x", "y", "z"};
    static constexpr const char *pnames3143[] {"x", "y", "z"};
    static constexpr const char *pnames3144[] {"x", "y", "z"};
    static constexpr const char *pnames3145[] {"v"};
    static constexpr const char *pnames3146[] {"v"};
    static constexpr const char *pnames3147[] {"v"};
    static constexpr const char *pnames3148[] {"x", "y", "z"};
    static constexpr const char *pnames3149[] {"x", "y", "z"};
    static constexpr const char *pnames3150[] {"x", "y", "z"};
    static constexpr const char *pnames3151[] {"v"};
    static constexpr const char *pnames3152[] {"v"};
    static constexpr const char *pnames3153[] {"v"};
    static constexpr const char *pnames3154[] {"x", "y", "z", "w"};
    static constexpr const char *pnames3155[] {"v"};
    static constexpr const char *pnames3156[] {"x", "y", "z", "w"};
    static constexpr const char *pnames3157[] {"v"};
    static constexpr const char *pnames3158[] {"x", "y", "z", "w"};
    static constexpr const char *pnames3159[] {"v"};
    static constexpr const char *pnames3160[] {"x", "y", "z", "w"};
    static constexpr const char *pnames3161[] {"v"};
    static constexpr const char *pnames3162[] {"mode", "count", "box"};
    static constexpr const char *pnames3163[] {"res", "in", "outX", "outY", "outZ", "outW"};
    static constexpr glfl::func_info ret[]
    {
        {"<0>", pnames0, '.', ""},
        {"glAccum", pnames1, '.', "E."},
        {"glAccumxOES", pnames2, '.', "E."},
        {"glActiveProgramEXT", pnames3, '.', "."},
        {"glActiveShaderProgram", pnames4, '.', ".."},
        {"glActiveShaderProgramEXT", pnames5, '.', ".."},
        {"glActiveStencilFaceEXT", pnames6, '.', "E"},
        {"glActiveTexture", pnames7, '.', "E"},
        {"glActiveTextureARB", pnames8, '.', "E"},
        {"glActiveVaryingNV", pnames9, '.', ".."},
        {"glAlphaFragmentOp1ATI", pnames10, '.', "E....."},
        {"glAlphaFragmentOp2ATI", pnames11, '.', "E........"},
        {"glAlphaFragmentOp3ATI", pnames12, '.', "E..........."},
        {"glAlphaFunc", pnames13, '.', "E."},
        {"glAlphaFuncQCOM", pnames14, '.', "E."},
        {"glAlphaFuncx", pnames15, '.', "E."},
        {"glAlphaFuncxOES", pnames16, '.', "E."},
        {"glApplyFramebufferAttachmentCMAAINTEL", pnames17, '.', ""},
        {"glApplyTextureEXT", pnames18, '.', "E"},
        {"glAreProgramsResidentNV", pnames19, 'B', "..."},
        {"glAreTexturesResident", pnames20, 'B', "..."},
        {"glAreTexturesResidentEXT", pnames21, 'B', "..."},
        {"glArrayElement", pnames22, '.', "."},
        {"glArrayElementEXT", pnames23, '.', "."},
        {"glArrayObjectATI", pnames24, '.', "E.E..."},
        {"glAsyncMarkerSGIX", pnames25, '.', "."},
        {"glAttachObjectARB", pnames26, '.', ".."},
        {"glAttachShader", pnames27, '.', ".."},
        {"glBegin", pnames28, '.', "E"},
        {"glBeginConditionalRender", pnames29, '.', ".E"},
        {"glBeginConditionalRenderNV", pnames30, '.', ".E"},
        {"glBeginConditionalRenderNVX", pnames31, '.', "."},
        {"glBeginFragmentShaderATI", pnames32, '.', ""},
        {"glBeginOcclusionQueryNV", pnames33, '.', "."},
        {"glBeginPerfMonitorAMD", pnames34, '.', "."},
        {"glBeginPerfQueryINTEL", pnames35, '.', "."},
        {"glBeginQuery", pnames36, '.', "E."},
        {"glBeginQueryARB", pnames37, '.', "E."},
        {"glBeginQueryEXT", pnames38, '.', "E."},
        {"glBeginQueryIndexed", pnames39, '.', "E.."},
        {"glBeginTransformFeedback", pnames40, '.', "E"},
        {"glBeginTransformFeedbackEXT", pnames41, '.', "E"},
        {"glBeginTransformFeedbackNV", pnames42, '.', "E"},
        {"glBeginVertexShaderEXT", pnames43, '.', ""},
        {"glBeginVideoCaptureNV", pnames44, '.', "."},
        {"glBindAttribLocation", pnames45, '.', "..."},
        {"glBindAttribLocationARB", pnames46, '.', "..."},
        {"glBindBuffer", pnames47, '.', "E."},
        {"glBindBufferARB", pnames48, '.', "E."},
        {"glBindBufferBase", pnames49, '.', "E.."},
        {"glBindBufferBaseEXT", pnames50, '.', "E.."},
        {"glBindBufferBaseNV", pnames51, '.', "E.."},
        {"glBindBufferOffsetEXT", pnames52, '.', "E..."},
        {"glBindBufferOffsetNV", pnames53, '.', "E..."},
        {"glBindBufferRange", pnames54, '.', "E...."},
        {"glBindBufferRangeEXT", pnames55, '.', "E...."},
        {"glBindBufferRangeNV", pnames56, '.', "E...."},
        {"glBindBuffersBase", pnames57, '.', "E..."},
        {"glBindBuffersRange", pnames58, '.', "E....."},
        {"glBindFragDataLocation", pnames59, '.', "..."},
        {"glBindFragDataLocationEXT", pnames60, '.', "..."},
        {"glBindFragDataLocationIndexed", pnames61, '.', "...."},
        {"glBindFragDataLocationIndexedEXT", pnames62, '.', "...."},
        {"glBindFragmentShaderATI", pnames63, '.', "."},
        {"glBindFramebuffer", pnames64, '.', "E."},
        {"glBindFramebufferEXT", pnames65, '.', "E."},
        {"glBindFramebufferOES", pnames66, '.', "E."},
        {"glBindImageTexture", pnames67, '.', "...B.EE"},
        {"glBindImageTextureEXT", pnames68, '.', "...B.E."},
        {"glBindImageTextures", pnames69, '.', "..."},
        {"glBindLightParameterEXT", pnames70, '.', "EE"},
        {"glBindMaterialParameterEXT", pnames71, '.', "EE"},
        {"glBindMultiTextureEXT", pnames72, '.', "EE."},
        {"glBindParameterEXT", pnames73, '.', "E"},
        {"glBindProgramARB", pnames74, '.', "E."},
        {"glBindProgramNV", pnames75, '.', "E."},
        {"glBindProgramPipeline", pnames76, '.', "."},
        {"glBindProgramPipelineEXT", pnames77, '.', "."},
        {"glBindRenderbuffer", pnames78, '.', "E."},
        {"glBindRenderbufferEXT", pnames79, '.', "E."},
        {"glBindRenderbufferOES", pnames80, '.', "E."},
        {"glBindSampler", pnames81, '.', ".."},
        {"glBindSamplers", pnames82, '.', "..."},
        {"glBindTexGenParameterEXT", pnames83, '.', "EEE"},
        {"glBindTexture", pnames84, '.', "E."},
        {"glBindTextureEXT", pnames85, '.', "E."},
        {"glBindTextureUnit", pnames86, '.', ".."},
        {"glBindTextureUnitParameterEXT", pnames87, '.', "EE"},
        {"glBindTextures", pnames88, '.', "..."},
        {"glBindTransformFeedback", pnames89, '.', "E."},
        {"glBindTransformFeedbackNV", pnames90, '.', "E."},
        {"glBindVertexArray", pnames91, '.', "."},
        {"glBindVertexArrayAPPLE", pnames92, '.', "."},
        {"glBindVertexArrayOES", pnames93, '.', "."},
        {"glBindVertexBuffer", pnames94, '.', "...."},
        {"glBindVertexBuffers", pnames95, '.', "....."},
        {"glBindVertexShaderEXT", pnames96, '.', "."},
        {"glBindVideoCaptureStreamBufferNV", pnames97, '.', "..E."},
        {"glBindVideoCaptureStreamTextureNV", pnames98, '.', "..EE."},
        {"glBinormal3bEXT", pnames99, '.', "..."},
        {"glBinormal3bvEXT", pnames100, '.', "."},
        {"glBinormal3dEXT", pnames101, '.', "..."},
        {"glBinormal3dvEXT", pnames102, '.', "."},
        {"glBinormal3fEXT", pnames103, '.', "..."},
        {"glBinormal3fvEXT", pnames104, '.', "."},
        {"glBinormal3iEXT", pnames105, '.', "..."},
        {"glBinormal3ivEXT", pnames106, '.', "."},
        {"glBinormal3sEXT", pnames107, '.', "..."},
        {"glBinormal3svEXT", pnames108, '.', "."},
        {"glBinormalPointerEXT", pnames109, '.', "E.."},
        {"glBitmap", pnames110, '.', "......."},
        {"glBitmapxOES", pnames111, '.', "......."},
        {"glBlendBarrier", pnames112, '.', ""},
        {"glBlendBarrierKHR", pnames113, '.', ""},
        {"glBlendBarrierNV", pnames114, '.', ""},
        {"glBlendColor", pnames115, '.', "...."},
        {"glBlendColorEXT", pnames116, '.', "...."},
        {"glBlendColorxOES", pnames117, '.', "...."},
        {"glBlendEquation", pnames118, '.', "E"},
        {"glBlendEquationEXT", pnames119, '.', "E"},
        {"glBlendEquationIndexedAMD", pnames120, '.', ".E"},
        {"glBlendEquationOES", pnames121, '.', "E"},
        {"glBlendEquationSeparate", pnames122, '.', "EE"},
        {"glBlendEquationSeparateEXT", pnames123, '.', "EE"},
        {"glBlendEquationSeparateIndexedAMD", pnames124, '.', ".EE"},
        {"glBlendEquationSeparateOES", pnames125, '.', "EE"},
        {"glBlendEquationSeparatei", pnames126, '.', ".EE"},
        {"glBlendEquationSeparateiARB", pnames127, '.', ".EE"},
        {"glBlendEquationSeparateiEXT", pnames128, '.', ".EE"},
        {"glBlendEquationSeparateiOES", pnames129, '.', ".EE"},
        {"glBlendEquationi", pnames130, '.', ".E"},
        {"glBlendEquationiARB", pnames131, '.', ".E"},
        {"glBlendEquationiEXT", pnames132, '.', ".E"},
        {"glBlendEquationiOES", pnames133, '.', ".E"},
        {"glBlendFunc", pnames134, '.', "EE"},
        {"glBlendFuncIndexedAMD", pnames135, '.', ".EE"},
        {"glBlendFuncSeparate", pnames136, '.', "EEEE"},
        {"glBlendFuncSeparateEXT", pnames137, '.', "EEEE"},
        {"glBlendFuncSeparateINGR", pnames138, '.', "EEEE"},
        {"glBlendFuncSeparateIndexedAMD", pnames139, '.', ".EEEE"},
        {"glBlendFuncSeparateOES", pnames140, '.', "EEEE"},
        {"glBlendFuncSeparatei", pnames141, '.', ".EEEE"},
        {"glBlendFuncSeparateiARB", pnames142, '.', ".EEEE"},
        {"glBlendFuncSeparateiEXT", pnames143, '.', ".EEEE"},
        {"glBlendFuncSeparateiOES", pnames144, '.', ".EEEE"},
        {"glBlendFunci", pnames145, '.', ".EE"},
        {"glBlendFunciARB", pnames146, '.', ".EE"},
        {"glBlendFunciEXT", pnames147, '.', ".EE"},
        {"glBlendFunciOES", pnames148, '.', ".EE"},
        {"glBlendParameteriNV", pnames149, '.', "E."},
        {"glBlitFramebuffer", pnames150, '.', "........FE"},
        {"glBlitFramebufferANGLE", pnames151, '.', "........FE"},
        {"glBlitFramebufferEXT", pnames152, '.', "........FE"},
        {"glBlitFramebufferNV", pnames153, '.', "........FE"},
        {"glBlitNamedFramebuffer", pnames154, '.', "..........FE"},
        {"glBufferAddressRangeNV", pnames155, '.', "E..."},
        {"glBufferData", pnames156, '.', "E..E"},
        {"glBufferDataARB", pnames157, '.', "E..E"},
        {"glBufferPageCommitmentARB", pnames158, '.', "E..B"},
        {"glBufferParameteriAPPLE", pnames159, '.', "EE."},
        {"glBufferStorage", pnames160, '.', "E..F"},
        {"glBufferStorageEXT", pnames161, '.', "E..F"},
        {"glBufferSubData", pnames162, '.', "E..."},
        {"glBufferSubDataARB", pnames163, '.', "E..."},
        {"glCallCommandListNV", pnames164, '.', "."},
        {"glCallList", pnames165, '.', "."},
        {"glCallLists", pnames166, '.', ".E."},
        {"glCheckFramebufferStatus", pnames167, 'E', "E"},
        {"glCheckFramebufferStatusEXT", pnames168, 'E', "E"},
        {"glCheckFramebufferStatusOES", pnames169, 'E', "E"},
        {"glCheckNamedFramebufferStatus", pnames170, 'E', ".E"},
        {"glCheckNamedFramebufferStatusEXT", pnames171, 'E', ".E"},
        {"glClampColor", pnames172, '.', "EE"},
        {"glClampColorARB", pnames173, '.', "EE"},
        {"glClear", pnames174, '.', "F"},
        {"glClearAccum", pnames175, '.', "...."},
        {"glClearAccumxOES", pnames176, '.', "...."},
        {"glClearBufferData", pnames177, '.', "EEEE."},
        {"glClearBufferSubData", pnames178, '.', "EE..EE."},
        {"glClearBufferfi", pnames179, '.', "E..."},
        {"glClearBufferfv", pnames180, '.', "E.."},
        {"glClearBufferiv", pnames181, '.', "E.."},
        {"glClearBufferuiv", pnames182, '.', "E.."},
        {"glClearColor", pnames183, '.', "...."},
        {"glClearColorIiEXT", pnames184, '.', "...."},
        {"glClearColorIuiEXT", pnames185, '.', "...."},
        {"glClearColorx", pnames186, '.', "...."},
        {"glClearColorxOES", pnames187, '.', "...."},
        {"glClearDepth", pnames188, '.', "."},
        {"glClearDepthdNV", pnames189, '.', "."},
        {"glClearDepthf", pnames190, '.', "."},
        {"glClearDepthfOES", pnames191, '.', "."},
        {"glClearDepthx", pnames192, '.', "."},
        {"glClearDepthxOES", pnames193, '.', "."},
        {"glClearIndex", pnames194, '.', "."},
        {"glClearNamedBufferData", pnames195, '.', ".EEE."},
        {"glClearNamedBufferDataEXT", pnames196, '.', ".EEE."},
        {"glClearNamedBufferSubData", pnames197, '.', ".E..EE."},
        {"glClearNamedBufferSubDataEXT", pnames198, '.', ".E..EE."},
        {"glClearNamedFramebufferfi", pnames199, '.', ".E..."},
        {"glClearNamedFramebufferfv", pnames200, '.', ".E.."},
        {"glClearNamedFramebufferiv", pnames201, '.', ".E.."},
        {"glClearNamedFramebufferuiv", pnames202, '.', ".E.."},
        {"glClearPixelLocalStorageuiEXT", pnames203, '.', "..."},
        {"glClearStencil", pnames204, '.', "."},
        {"glClearTexImage", pnames205, '.', "..EE."},
        {"glClearTexImageEXT", pnames206, '.', "..EE."},
        {"glClearTexSubImage", pnames207, '.', "........EE."},
        {"glClearTexSubImageEXT", pnames208, '.', "........EE."},
        {"glClientActiveTexture", pnames209, '.', "E"},
        {"glClientActiveTextureARB", pnames210, '.', "E"},
        {"glClientActiveVertexStreamATI", pnames211, '.', "E"},
        {"glClientAttribDefaultEXT", pnames212, '.', "F"},
        {"glClientWaitSync", pnames213, 'E', ".F."},
        {"glClientWaitSyncAPPLE", pnames214, 'E', ".F."},
        {"glClipControl", pnames215, '.', "EE"},
        {"glClipPlane", pnames216, '.', "E."},
        {"glClipPlanef", pnames217, '.', "E."},
        {"glClipPlanefIMG", pnames218, '.', "E."},
        {"glClipPlanefOES", pnames219, '.', "E."},
        {"glClipPlanex", pnames220, '.', "E."},
        {"glClipPlanexIMG", pnames221, '.', "E."},
        {"glClipPlanexOES", pnames222, '.', "E."},
        {"glColor3b", pnames223, '.', "..."},
        {"glColor3bv", pnames224, '.', "."},
        {"glColor3d", pnames225, '.', "..."},
        {"glColor3dv", pnames226, '.', "."},
        {"glColor3f", pnames227, '.', "..."},
        {"glColor3fVertex3fSUN", pnames228, '.', "......"},
        {"glColor3fVertex3fvSUN", pnames229, '.', ".."},
        {"glColor3fv", pnames230, '.', "."},
        {"glColor3hNV", pnames231, '.', "..."},
        {"glColor3hvNV", pnames232, '.', "."},
        {"glColor3i", pnames233, '.', "..."},
        {"glColor3iv", pnames234, '.', "."},
        {"glColor3s", pnames235, '.', "..."},
        {"glColor3sv", pnames236, '.', "."},
        {"glColor3ub", pnames237, '.', "..."},
        {"glColor3ubv", pnames238, '.', "."},
        {"glColor3ui", pnames239, '.', "..."},
        {"glColor3uiv", pnames240, '.', "."},
        {"glColor3us", pnames241, '.', "..."},
        {"glColor3usv", pnames242, '.', "."},
        {"glColor3xOES", pnames243, '.', "..."},
        {"glColor3xvOES", pnames244, '.', "."},
        {"glColor4b", pnames245, '.', "...."},
        {"glColor4bv", pnames246, '.', "."},
        {"glColor4d", pnames247, '.', "...."},
        {"glColor4dv", pnames248, '.', "."},
        {"glColor4f", pnames249, '.', "...."},
        {"glColor4fNormal3fVertex3fSUN", pnames250, '.', ".........."},
        {"glColor4fNormal3fVertex3fvSUN", pnames251, '.', "..."},
        {"glColor4fv", pnames252, '.', "."},
        {"glColor4hNV", pnames253, '.', "...."},
        {"glColor4hvNV", pnames254, '.', "."},
        {"glColor4i", pnames255, '.', "...."},
        {"glColor4iv", pnames256, '.', "."},
        {"glColor4s", pnames257, '.', "...."},
        {"glColor4sv", pnames258, '.', "."},
        {"glColor4ub", pnames259, '.', "...."},
        {"glColor4ubVertex2fSUN", pnames260, '.', "......"},
        {"glColor4ubVertex2fvSUN", pnames261, '.', ".."},
        {"glColor4ubVertex3fSUN", pnames262, '.', "......."},
        {"glColor4ubVertex3fvSUN", pnames263, '.', ".."},
        {"glColor4ubv", pnames264, '.', "."},
        {"glColor4ui", pnames265, '.', "...."},
        {"glColor4uiv", pnames266, '.', "."},
        {"glColor4us", pnames267, '.', "...."},
        {"glColor4usv", pnames268, '.', "."},
        {"glColor4x", pnames269, '.', "...."},
        {"glColor4xOES", pnames270, '.', "...."},
        {"glColor4xvOES", pnames271, '.', "."},
        {"glColorFormatNV", pnames272, '.', ".E."},
        {"glColorFragmentOp1ATI", pnames273, '.', "E......"},
        {"glColorFragmentOp2ATI", pnames274, '.', "E........."},
        {"glColorFragmentOp3ATI", pnames275, '.', "E............"},
        {"glColorMask", pnames276, '.', "BBBB"},
        {"glColorMaskIndexedEXT", pnames277, '.', ".BBBB"},
        {"glColorMaski", pnames278, '.', ".BBBB"},
        {"glColorMaskiEXT", pnames279, '.', ".BBBB"},
        {"glColorMaskiOES", pnames280, '.', ".BBBB"},
        {"glColorMaterial", pnames281, '.', "EE"},
        {"glColorP3ui", pnames282, '.', "E."},
        {"glColorP3uiv", pnames283, '.', "E."},
        {"glColorP4ui", pnames284, '.', "E."},
        {"glColorP4uiv", pnames285, '.', "E."},
        {"glColorPointer", pnames286, '.', ".E.."},
        {"glColorPointerEXT", pnames287, '.', ".E..."},
        {"glColorPointerListIBM", pnames288, '.', ".E..."},
        {"glColorPointervINTEL", pnames289, '.', ".E."},
        {"glColorSubTable", pnames290, '.', "E..EE."},
        {"glColorSubTableEXT", pnames291, '.', "E..EE."},
        {"glColorTable", pnames292, '.', "EE.EE."},
        {"glColorTableEXT", pnames293, '.', "EE.EE."},
        {"glColorTableParameterfv", pnames294, '.', "EE."},
        {"glColorTableParameterfvSGI", pnames295, '.', "EE."},
        {"glColorTableParameteriv", pnames296, '.', "EE."},
        {"glColorTableParameterivSGI", pnames297, '.', "EE."},
        {"glColorTableSGI", pnames298, '.', "EE.EE."},
        {"glCombinerInputNV", pnames299, '.', "EEEEEE"},
        {"glCombinerOutputNV", pnames300, '.', "EEEEEEEBBB"},
        {"glCombinerParameterfNV", pnames301, '.', "E."},
        {"glCombinerParameterfvNV", pnames302, '.', "E."},
        {"glCombinerParameteriNV", pnames303, '.', "E."},
        {"glCombinerParameterivNV", pnames304, '.', "E."},
        {"glCombinerStageParameterfvNV", pnames305, '.', "EE."},
        {"glCommandListSegmentsNV", pnames306, '.', ".."},
        {"glCompileCommandListNV", pnames307, '.', "."},
        {"glCompileShader", pnames308, '.', "."},
        {"glCompileShaderARB", pnames309, '.', "."},
        {"glCompileShaderIncludeARB", pnames310, '.', "...."},
        {"glCompressedMultiTexImage1DEXT", pnames311, '.', "EE.E...."},
        {"glCompressedMultiTexImage2DEXT", pnames312, '.', "EE.E....."},
        {"glCompressedMultiTexImage3DEXT", pnames313, '.', "EE.E......"},
        {"glCompressedMultiTexSubImage1DEXT", pnames314, '.', "EE...E.."},
        {"glCompressedMultiTexSubImage2DEXT", pnames315, '.', "EE.....E.."},
        {"glCompressedMultiTexSubImage3DEXT", pnames316, '.', "EE.......E.."},
        {"glCompressedTexImage1D", pnames317, '.', "E.E...."},
        {"glCompressedTexImage1DARB", pnames318, '.', "E.E...."},
        {"glCompressedTexImage2D", pnames319, '.', "E.E....."},
        {"glCompressedTexImage2DARB", pnames320, '.', "E.E....."},
        {"glCompressedTexImage3D", pnames321, '.', "E.E......"},
        {"glCompressedTexImage3DARB", pnames322, '.', "E.E......"},
        {"glCompressedTexImage3DOES", pnames323, '.', "E.E......"},
        {"glCompressedTexSubImage1D", pnames324, '.', "E...E.."},
        {"glCompressedTexSubImage1DARB", pnames325, '.', "E...E.."},
        {"glCompressedTexSubImage2D", pnames326, '.', "E.....E.."},
        {"glCompressedTexSubImage2DARB", pnames327, '.', "E.....E.."},
        {"glCompressedTexSubImage3D", pnames328, '.', "E.......E.."},
        {"glCompressedTexSubImage3DARB", pnames329, '.', "E.......E.."},
        {"glCompressedTexSubImage3DOES", pnames330, '.', "E.......E.."},
        {"glCompressedTextureImage1DEXT", pnames331, '.', ".E.E...."},
        {"glCompressedTextureImage2DEXT", pnames332, '.', ".E.E....."},
        {"glCompressedTextureImage3DEXT", pnames333, '.', ".E.E......"},
        {"glCompressedTextureSubImage1D", pnames334, '.', "....E.."},
        {"glCompressedTextureSubImage1DEXT", pnames335, '.', ".E...E.."},
        {"glCompressedTextureSubImage2D", pnames336, '.', "......E.."},
        {"glCompressedTextureSubImage2DEXT", pnames337, '.', ".E.....E.."},
        {"glCompressedTextureSubImage3D", pnames338, '.', "........E.."},
        {"glCompressedTextureSubImage3DEXT", pnames339, '.', ".E.......E.."},
        {"glConservativeRasterParameterfNV", pnames340, '.', "E."},
        {"glConservativeRasterParameteriNV", pnames341, '.', "E."},
        {"glConvolutionFilter1D", pnames342, '.', "EE.EE."},
        {"glConvolutionFilter1DEXT", pnames343, '.', "EE.EE."},
        {"glConvolutionFilter2D", pnames344, '.', "EE..EE."},
        {"glConvolutionFilter2DEXT", pnames345, '.', "EE..EE."},
        {"glConvolutionParameterf", pnames346, '.', "EE."},
        {"glConvolutionParameterfEXT", pnames347, '.', "EE."},
        {"glConvolutionParameterfv", pnames348, '.', "EE."},
        {"glConvolutionParameterfvEXT", pnames349, '.', "EE."},
        {"glConvolutionParameteri", pnames350, '.', "EE."},
        {"glConvolutionParameteriEXT", pnames351, '.', "EE."},
        {"glConvolutionParameteriv", pnames352, '.', "EE."},
        {"glConvolutionParameterivEXT", pnames353, '.', "EE."},
        {"glConvolutionParameterxOES", pnames354, '.', "EE."},
        {"glConvolutionParameterxvOES", pnames355, '.', "EE."},
        {"glCopyBufferSubData", pnames356, '.', "EE..."},
        {"glCopyBufferSubDataNV", pnames357, '.', "EE..."},
        {"glCopyColorSubTable", pnames358, '.', "E...."},
        {"glCopyColorSubTableEXT", pnames359, '.', "E...."},
        {"glCopyColorTable", pnames360, '.', "EE..."},
        {"glCopyColorTableSGI", pnames361, '.', "EE..."},
        {"glCopyConvolutionFilter1D", pnames362, '.', "EE..."},
        {"glCopyConvolutionFilter1DEXT", pnames363, '.', "EE..."},
        {"glCopyConvolutionFilter2D", pnames364, '.', "EE...."},
        {"glCopyConvolutionFilter2DEXT", pnames365, '.', "EE...."},
        {"glCopyImageSubData", pnames366, '.', ".E.....E......."},
        {"glCopyImageSubDataEXT", pnames367, '.', ".E.....E......."},
        {"glCopyImageSubDataNV", pnames368, '.', ".E.....E......."},
        {"glCopyImageSubDataOES", pnames369, '.', ".E.....E......."},
        {"glCopyMultiTexImage1DEXT", pnames370, '.', "EE.E...."},
        {"glCopyMultiTexImage2DEXT", pnames371, '.', "EE.E....."},
        {"glCopyMultiTexSubImage1DEXT", pnames372, '.', "EE....."},
        {"glCopyMultiTexSubImage2DEXT", pnames373, '.', "EE......."},
        {"glCopyMultiTexSubImage3DEXT", pnames374, '.', "EE........"},
        {"glCopyNamedBufferSubData", pnames375, '.', "....."},
        {"glCopyPathNV", pnames376, '.', ".."},
        {"glCopyPixels", pnames377, '.', "....E"},
        {"glCopyTexImage1D", pnames378, '.', "E.E...."},
        {"glCopyTexImage1DEXT", pnames379, '.', "E.E...."},
        {"glCopyTexImage2D", pnames380, '.', "E.E....."},
        {"glCopyTexImage2DEXT", pnames381, '.', "E.E....."},
        {"glCopyTexSubImage1D", pnames382, '.', "E....."},
        {"glCopyTexSubImage1DEXT", pnames383, '.', "E....."},
        {"glCopyTexSubImage2D", pnames384, '.', "E......."},
        {"glCopyTexSubImage2DEXT", pnames385, '.', "E......."},
        {"glCopyTexSubImage3D", pnames386, '.', "E........"},
        {"glCopyTexSubImage3DEXT", pnames387, '.', "E........"},
        {"glCopyTexSubImage3DOES", pnames388, '.', "E........"},
        {"glCopyTextureImage1DEXT", pnames389, '.', ".E.E...."},
        {"glCopyTextureImage2DEXT", pnames390, '.', ".E.E....."},
        {"glCopyTextureLevelsAPPLE", pnames391, '.', "...."},
        {"glCopyTextureSubImage1D", pnames392, '.', "......"},
        {"glCopyTextureSubImage1DEXT", pnames393, '.', ".E....."},
        {"glCopyTextureSubImage2D", pnames394, '.', "........"},
        {"glCopyTextureSubImage2DEXT", pnames395, '.', ".E......."},
        {"glCopyTextureSubImage3D", pnames396, '.', "........."},
        {"glCopyTextureSubImage3DEXT", pnames397, '.', ".E........"},
        {"glCoverFillPathInstancedNV", pnames398, '.', ".E..EE."},
        {"glCoverFillPathNV", pnames399, '.', ".E"},
        {"glCoverStrokePathInstancedNV", pnames400, '.', ".E..EE."},
        {"glCoverStrokePathNV", pnames401, '.', ".E"},
        {"glCoverageMaskNV", pnames402, '.', "B"},
        {"glCoverageModulationNV", pnames403, '.', "E"},
        {"glCoverageModulationTableNV", pnames404, '.', ".."},
        {"glCoverageOperationNV", pnames405, '.', "E"},
        {"glCreateBuffers", pnames406, '.', ".."},
        {"glCreateCommandListsNV", pnames407, '.', ".."},
        {"glCreateFramebuffers", pnames408, '.', ".."},
        {"glCreatePerfQueryINTEL", pnames409, '.', ".."},
        {"glCreateProgram", pnames410, '.', ""},
        {"glCreateProgramObjectARB", pnames411, '.', ""},
        {"glCreateProgramPipelines", pnames412, '.', ".."},
        {"glCreateQueries", pnames413, '.', "E.."},
        {"glCreateRenderbuffers", pnames414, '.', ".."},
        {"glCreateSamplers", pnames415, '.', ".."},
        {"glCreateShader", pnames416, '.', "E"},
        {"glCreateShaderObjectARB", pnames417, '.', "E"},
        {"glCreateShaderProgramEXT", pnames418, '.', "E."},
        {"glCreateShaderProgramv", pnames419, '.', "E.."},
        {"glCreateShaderProgramvEXT", pnames420, '.', "E.."},
        {"glCreateStatesNV", pnames421, '.', ".."},
        {"glCreateSyncFromCLeventARB", pnames422, '.', "..F"},
        {"glCreateTextures", pnames423, '.', "E.."},
        {"glCreateTransformFeedbacks", pnames424, '.', ".."},
        {"glCreateVertexArrays", pnames425, '.', ".."},
        {"glCullFace", pnames426, '.', "E"},
        {"glCullParameterdvEXT", pnames427, '.', "E."},
        {"glCullParameterfvEXT", pnames428, '.', "E."},
        {"glCurrentPaletteMatrixARB", pnames429, '.', "."},
        {"glCurrentPaletteMatrixOES", pnames430, '.', "."},
        {"glDebugMessageCallback", pnames431, '.', ".."},
        {"glDebugMessageCallbackAMD", pnames432, '.', ".."},
        {"glDebugMessageCallbackARB", pnames433, '.', ".."},
        {"glDebugMessageCallbackKHR", pnames434, '.', ".."},
        {"glDebugMessageControl", pnames435, '.', "EEE..B"},
        {"glDebugMessageControlARB", pnames436, '.', "EEE..B"},
        {"glDebugMessageControlKHR", pnames437, '.', "EEE..B"},
        {"glDebugMessageEnableAMD", pnames438, '.', "EE..B"},
        {"glDebugMessageInsert", pnames439, '.', "EE.E.."},
        {"glDebugMessageInsertAMD", pnames440, '.', "EE..."},
        {"glDebugMessageInsertARB", pnames441, '.', "EE.E.."},
        {"glDebugMessageInsertKHR", pnames442, '.', "EE.E.."},
        {"glDeformSGIX", pnames443, '.', "F"},
        {"glDeformationMap3dSGIX", pnames444, '.', "E............."},
        {"glDeformationMap3fSGIX", pnames445, '.', "E............."},
        {"glDeleteAsyncMarkersSGIX", pnames446, '.', ".."},
        {"glDeleteBuffers", pnames447, '.', ".."},
        {"glDeleteBuffersARB", pnames448, '.', ".."},
        {"glDeleteCommandListsNV", pnames449, '.', ".."},
        {"glDeleteFencesAPPLE", pnames450, '.', ".."},
        {"glDeleteFencesNV", pnames451, '.', ".."},
        {"glDeleteFragmentShaderATI", pnames452, '.', "."},
        {"glDeleteFramebuffers", pnames453, '.', ".."},
        {"glDeleteFramebuffersEXT", pnames454, '.', ".."},
        {"glDeleteFramebuffersOES", pnames455, '.', ".."},
        {"glDeleteLists", pnames456, '.', ".."},
        {"glDeleteNamedStringARB", pnames457, '.', ".."},
        {"glDeleteNamesAMD", pnames458, '.', "E.."},
        {"glDeleteObjectARB", pnames459, '.', "."},
        {"glDeleteOcclusionQueriesNV", pnames460, '.', ".."},
        {"glDeletePathsNV", pnames461, '.', ".."},
        {"glDeletePerfMonitorsAMD", pnames462, '.', ".."},
        {"glDeletePerfQueryINTEL", pnames463, '.', "."},
        {"glDeleteProgram", pnames464, '.', "."},
        {"glDeleteProgramPipelines", pnames465, '.', ".."},
        {"glDeleteProgramPipelinesEXT", pnames466, '.', ".."},
        {"glDeleteProgramsARB", pnames467, '.', ".."},
        {"glDeleteProgramsNV", pnames468, '.', ".."},
        {"glDeleteQueries", pnames469, '.', ".."},
        {"glDeleteQueriesARB", pnames470, '.', ".."},
        {"glDeleteQueriesEXT", pnames471, '.', ".."},
        {"glDeleteRenderbuffers", pnames472, '.', ".."},
        {"glDeleteRenderbuffersEXT", pnames473, '.', ".."},
        {"glDeleteRenderbuffersOES", pnames474, '.', ".."},
        {"glDeleteSamplers", pnames475, '.', ".."},
        {"glDeleteShader", pnames476, '.', "."},
        {"glDeleteStatesNV", pnames477, '.', ".."},
        {"glDeleteSync", pnames478, '.', "."},
        {"glDeleteSyncAPPLE", pnames479, '.', "."},
        {"glDeleteTextures", pnames480, '.', ".."},
        {"glDeleteTexturesEXT", pnames481, '.', ".."},
        {"glDeleteTransformFeedbacks", pnames482, '.', ".."},
        {"glDeleteTransformFeedbacksNV", pnames483, '.', ".."},
        {"glDeleteVertexArrays", pnames484, '.', ".."},
        {"glDeleteVertexArraysAPPLE", pnames485, '.', ".."},
        {"glDeleteVertexArraysOES", pnames486, '.', ".."},
        {"glDeleteVertexShaderEXT", pnames487, '.', "."},
        {"glDepthBoundsEXT", pnames488, '.', ".."},
        {"glDepthBoundsdNV", pnames489, '.', ".."},
        {"glDepthFunc", pnames490, '.', "E"},
        {"glDepthMask", pnames491, '.', "B"},
        {"glDepthRange", pnames492, '.', ".."},
        {"glDepthRangeArrayfvNV", pnames493, '.', "..."},
        {"glDepthRangeArrayfvOES", pnames494, '.', "..."},
        {"glDepthRangeArrayv", pnames495, '.', "..."},
        {"glDepthRangeIndexed", pnames496, '.', "..."},
        {"glDepthRangeIndexedfNV", pnames497, '.', "..."},
        {"glDepthRangeIndexedfOES", pnames498, '.', "..."},
        {"glDepthRangedNV", pnames499, '.', ".."},
        {"glDepthRangef", pnames500, '.', ".."},
        {"glDepthRangefOES", pnames501, '.', ".."},
        {"glDepthRangex", pnames502, '.', ".."},
        {"glDepthRangexOES", pnames503, '.', ".."},
        {"glDetachObjectARB", pnames504, '.', ".."},
        {"glDetachShader", pnames505, '.', ".."},
        {"glDetailTexFuncSGIS", pnames506, '.', "E.."},
        {"glDisable", pnames507, '.', "E"},
        {"glDisableClientState", pnames508, '.', "E"},
        {"glDisableClientStateIndexedEXT", pnames509, '.', "E."},
        {"glDisableClientStateiEXT", pnames510, '.', "E."},
        {"glDisableDriverControlQCOM", pnames511, '.', "."},
        {"glDisableIndexedEXT", pnames512, '.', "E."},
        {"glDisableVariantClientStateEXT", pnames513, '.', "."},
        {"glDisableVertexArrayAttrib", pnames514, '.', ".."},
        {"glDisableVertexArrayAttribEXT", pnames515, '.', ".."},
        {"glDisableVertexArrayEXT", pnames516, '.', ".E"},
        {"glDisableVertexAttribAPPLE", pnames517, '.', ".E"},
        {"glDisableVertexAttribArray", pnames518, '.', "."},
        {"glDisableVertexAttribArrayARB", pnames519, '.', "."},
        {"glDisablei", pnames520, '.', "E."},
        {"glDisableiEXT", pnames521, '.', "E."},
        {"glDisableiNV", pnames522, '.', "E."},
        {"glDisableiOES", pnames523, '.', "E."},
        {"glDiscardFramebufferEXT", pnames524, '.', "E.."},
        {"glDispatchCompute", pnames525, '.', "..."},
        {"glDispatchComputeGroupSizeARB", pnames526, '.', "......"},
        {"glDispatchComputeIndirect", pnames527, '.', "."},
        {"glDrawArrays", pnames528, '.', "E.."},
        {"glDrawArraysEXT", pnames529, '.', "E.."},
        {"glDrawArraysIndirect", pnames530, '.', "E."},
        {"glDrawArraysInstanced", pnames531, '.', "E..."},
        {"glDrawArraysInstancedANGLE", pnames532, '.', "E..."},
        {"glDrawArraysInstancedARB", pnames533, '.', "E..."},
        {"glDrawArraysInstancedBaseInstance", pnames534, '.', "E...."},
        {"glDrawArraysInstancedBaseInstanceEXT", pnames535, '.', "E...."},
        {"glDrawArraysInstancedEXT", pnames536, '.', "E..."},
        {"glDrawArraysInstancedNV", pnames537, '.', "E..."},
        {"glDrawBuffer", pnames538, '.', "E"},
        {"glDrawBuffers", pnames539, '.', ".."},
        {"glDrawBuffersARB", pnames540, '.', ".."},
        {"glDrawBuffersATI", pnames541, '.', ".."},
        {"glDrawBuffersEXT", pnames542, '.', ".."},
        {"glDrawBuffersIndexedEXT", pnames543, '.', "..."},
        {"glDrawBuffersNV", pnames544, '.', ".."},
        {"glDrawCommandsAddressNV", pnames545, '.', "E..."},
        {"glDrawCommandsNV", pnames546, '.', "E...."},
        {"glDrawCommandsStatesAddressNV", pnames547, '.', "....."},
        {"glDrawCommandsStatesNV", pnames548, '.', "......"},
        {"glDrawElementArrayAPPLE", pnames549, '.', "E.."},
        {"glDrawElementArrayATI", pnames550, '.', "E."},
        {"glDrawElements", pnames551, '.', "E.E."},
        {"glDrawElementsBaseVertex", pnames552, '.', "E.E.."},
        {"glDrawElementsBaseVertexEXT", pnames553, '.', "E.E.."},
        {"glDrawElementsBaseVertexOES", pnames554, '.', "E.E.."},
        {"glDrawElementsIndirect", pnames555, '.', "EE."},
        {"glDrawElementsInstanced", pnames556, '.', "E.E.."},
        {"glDrawElementsInstancedANGLE", pnames557, '.', "E.E.."},
        {"glDrawElementsInstancedARB", pnames558, '.', "E.E.."},
        {"glDrawElementsInstancedBaseInstance", pnames559, '.', "E.E..."},
        {"glDrawElementsInstancedBaseInstanceEXT", pnames560, '.', "E.E..."},
        {"glDrawElementsInstancedBaseVertex", pnames561, '.', "E.E..."},
        {"glDrawElementsInstancedBaseVertexBaseInstance", pnames562, '.', "E.E...."},
        {"glDrawElementsInstancedBaseVertexBaseInstanceEXT", pnames563, '.', "E.E...."},
        {"glDrawElementsInstancedBaseVertexEXT", pnames564, '.', "E.E..."},
        {"glDrawElementsInstancedBaseVertexOES", pnames565, '.', "E.E..."},
        {"glDrawElementsInstancedEXT", pnames566, '.', "E.E.."},
        {"glDrawElementsInstancedNV", pnames567, '.', "E.E.."},
        {"glDrawMeshArraysSUN", pnames568, '.', "E..."},
        {"glDrawPixels", pnames569, '.', "..EE."},
        {"glDrawRangeElementArrayAPPLE", pnames570, '.', "E...."},
        {"glDrawRangeElementArrayATI", pnames571, '.', "E..."},
        {"glDrawRangeElements", pnames572, '.', "E...E."},
        {"glDrawRangeElementsBaseVertex", pnames573, '.', "E...E.."},
        {"glDrawRangeElementsBaseVertexEXT", pnames574, '.', "E...E.."},
        {"glDrawRangeElementsBaseVertexOES", pnames575, '.', "E...E.."},
        {"glDrawRangeElementsEXT", pnames576, '.', "E...E."},
        {"glDrawTexfOES", pnames577, '.', "....."},
        {"glDrawTexfvOES", pnames578, '.', "."},
        {"glDrawTexiOES", pnames579, '.', "....."},
        {"glDrawTexivOES", pnames580, '.', "."},
        {"glDrawTexsOES", pnames581, '.', "....."},
        {"glDrawTexsvOES", pnames582, '.', "."},
        {"glDrawTextureNV", pnames583, '.', "..........."},
        {"glDrawTexxOES", pnames584, '.', "....."},
        {"glDrawTexxvOES", pnames585, '.', "."},
        {"glDrawTransformFeedback", pnames586, '.', "E."},
        {"glDrawTransformFeedbackEXT", pnames587, '.', "E."},
        {"glDrawTransformFeedbackInstanced", pnames588, '.', "E.."},
        {"glDrawTransformFeedbackInstancedEXT", pnames589, '.', "E.."},
        {"glDrawTransformFeedbackNV", pnames590, '.', "E."},
        {"glDrawTransformFeedbackStream", pnames591, '.', "E.."},
        {"glDrawTransformFeedbackStreamInstanced", pnames592, '.', "E..."},
        {"glEGLImageTargetRenderbufferStorageOES", pnames593, '.', "E."},
        {"glEGLImageTargetTexture2DOES", pnames594, '.', "E."},
        {"glEdgeFlag", pnames595, '.', "B"},
        {"glEdgeFlagFormatNV", pnames596, '.', "."},
        {"glEdgeFlagPointer", pnames597, '.', ".."},
        {"glEdgeFlagPointerEXT", pnames598, '.', "..."},
        {"glEdgeFlagPointerListIBM", pnames599, '.', "..."},
        {"glEdgeFlagv", pnames600, '.', "."},
        {"glElementPointerAPPLE", pnames601, '.', "E."},
        {"glElementPointerATI", pnames602, '.', "E."},
        {"glEnable", pnames603, '.', "E"},
        {"glEnableClientState", pnames604, '.', "E"},
        {"glEnableClientStateIndexedEXT", pnames605, '.', "E."},
        {"glEnableClientStateiEXT", pnames606, '.', "E."},
        {"glEnableDriverControlQCOM", pnames607, '.', "."},
        {"glEnableIndexedEXT", pnames608, '.', "E."},
        {"glEnableVariantClientStateEXT", pnames609, '.', "."},
        {"glEnableVertexArrayAttrib", pnames610, '.', ".."},
        {"glEnableVertexArrayAttribEXT", pnames611, '.', ".."},
        {"glEnableVertexArrayEXT", pnames612, '.', ".E"},
        {"glEnableVertexAttribAPPLE", pnames613, '.', ".E"},
        {"glEnableVertexAttribArray", pnames614, '.', "."},
        {"glEnableVertexAttribArrayARB", pnames615, '.', "."},
        {"glEnablei", pnames616, '.', "E."},
        {"glEnableiEXT", pnames617, '.', "E."},
        {"glEnableiNV", pnames618, '.', "E."},
        {"glEnableiOES", pnames619, '.', "E."},
        {"glEnd", pnames620, '.', ""},
        {"glEndConditionalRender", pnames621, '.', ""},
        {"glEndConditionalRenderNV", pnames622, '.', ""},
        {"glEndConditionalRenderNVX", pnames623, '.', ""},
        {"glEndFragmentShaderATI", pnames624, '.', ""},
        {"glEndList", pnames625, '.', ""},
        {"glEndOcclusionQueryNV", pnames626, '.', ""},
        {"glEndPerfMonitorAMD", pnames627, '.', "."},
        {"glEndPerfQueryINTEL", pnames628, '.', "."},
        {"glEndQuery", pnames629, '.', "E"},
        {"glEndQueryARB", pnames630, '.', "E"},
        {"glEndQueryEXT", pnames631, '.', "E"},
        {"glEndQueryIndexed", pnames632, '.', "E."},
        {"glEndTilingQCOM", pnames633, '.', "F"},
        {"glEndTransformFeedback", pnames634, '.', ""},
        {"glEndTransformFeedbackEXT", pnames635, '.', ""},
        {"glEndTransformFeedbackNV", pnames636, '.', ""},
        {"glEndVertexShaderEXT", pnames637, '.', ""},
        {"glEndVideoCaptureNV", pnames638, '.', "."},
        {"glEvalCoord1d", pnames639, '.', "."},
        {"glEvalCoord1dv", pnames640, '.', "."},
        {"glEvalCoord1f", pnames641, '.', "."},
        {"glEvalCoord1fv", pnames642, '.', "."},
        {"glEvalCoord1xOES", pnames643, '.', "."},
        {"glEvalCoord1xvOES", pnames644, '.', "."},
        {"glEvalCoord2d", pnames645, '.', ".."},
        {"glEvalCoord2dv", pnames646, '.', "."},
        {"glEvalCoord2f", pnames647, '.', ".."},
        {"glEvalCoord2fv", pnames648, '.', "."},
        {"glEvalCoord2xOES", pnames649, '.', ".."},
        {"glEvalCoord2xvOES", pnames650, '.', "."},
        {"glEvalMapsNV", pnames651, '.', "EE"},
        {"glEvalMesh1", pnames652, '.', "E.."},
        {"glEvalMesh2", pnames653, '.', "E...."},
        {"glEvalPoint1", pnames654, '.', "."},
        {"glEvalPoint2", pnames655, '.', ".."},
        {"glEvaluateDepthValuesARB", pnames656, '.', ""},
        {"glExecuteProgramNV", pnames657, '.', "E.."},
        {"glExtGetBufferPointervQCOM", pnames658, '.', "E."},
        {"glExtGetBuffersQCOM", pnames659, '.', "..."},
        {"glExtGetFramebuffersQCOM", pnames660, '.', "..."},
        {"glExtGetProgramBinarySourceQCOM", pnames661, '.', ".E.."},
        {"glExtGetProgramsQCOM", pnames662, '.', "..."},
        {"glExtGetRenderbuffersQCOM", pnames663, '.', "..."},
        {"glExtGetShadersQCOM", pnames664, '.', "..."},
        {"glExtGetTexLevelParameterivQCOM", pnames665, '.', ".E.E."},
        {"glExtGetTexSubImageQCOM", pnames666, '.', "E.......EE."},
        {"glExtGetTexturesQCOM", pnames667, '.', "..."},
        {"glExtIsProgramBinaryQCOM", pnames668, 'B', "."},
        {"glExtTexObjectStateOverrideiQCOM", pnames669, '.', "EE."},
        {"glExtractComponentEXT", pnames670, '.', "..."},
        {"glFeedbackBuffer", pnames671, '.', ".E."},
        {"glFeedbackBufferxOES", pnames672, '.', ".E."},
        {"glFenceSync", pnames673, '.', "EF"},
        {"glFenceSyncAPPLE", pnames674, '.', "EF"},
        {"glFinalCombinerInputNV", pnames675, '.', "EEEE"},
        {"glFinish", pnames676, '.', ""},
        {"glFinishAsyncSGIX", pnames677, '.', "."},
        {"glFinishFenceAPPLE", pnames678, '.', "."},
        {"glFinishFenceNV", pnames679, '.', "."},
        {"glFinishObjectAPPLE", pnames680, '.', "E."},
        {"glFinishTextureSUNX", pnames681, '.', ""},
        {"glFlush", pnames682, '.', ""},
        {"glFlushMappedBufferRange", pnames683, '.', "E.."},
        {"glFlushMappedBufferRangeAPPLE", pnames684, '.', "E.."},
        {"glFlushMappedBufferRangeEXT", pnames685, '.', "E.."},
        {"glFlushMappedNamedBufferRange", pnames686, '.', "..."},
        {"glFlushMappedNamedBufferRangeEXT", pnames687, '.', "..."},
        {"glFlushPixelDataRangeNV", pnames688, '.', "E"},
        {"glFlushRasterSGIX", pnames689, '.', ""},
        {"glFlushStaticDataIBM", pnames690, '.', "E"},
        {"glFlushVertexArrayRangeAPPLE", pnames691, '.', ".."},
        {"glFlushVertexArrayRangeNV", pnames692, '.', ""},
        {"glFogCoordFormatNV", pnames693, '.', "E."},
        {"glFogCoordPointer", pnames694, '.', "E.."},
        {"glFogCoordPointerEXT", pnames695, '.', "E.."},
        {"glFogCoordPointerListIBM", pnames696, '.', "E..."},
        {"glFogCoordd", pnames697, '.', "."},
        {"glFogCoorddEXT", pnames698, '.', "."},
        {"glFogCoorddv", pnames699, '.', "."},
        {"glFogCoorddvEXT", pnames700, '.', "."},
        {"glFogCoordf", pnames701, '.', "."},
        {"glFogCoordfEXT", pnames702, '.', "."},
        {"glFogCoordfv", pnames703, '.', "."},
        {"glFogCoordfvEXT", pnames704, '.', "."},
        {"glFogCoordhNV", pnames705, '.', "."},
        {"glFogCoordhvNV", pnames706, '.', "."},
        {"glFogFuncSGIS", pnames707, '.', ".."},
        {"glFogf", pnames708, '.', "E."},
        {"glFogfv", pnames709, '.', "E."},
        {"glFogi", pnames710, '.', "E."},
        {"glFogiv", pnames711, '.', "E."},
        {"glFogx", pnames712, '.', "E."},
        {"glFogxOES", pnames713, '.', "E."},
        {"glFogxv", pnames714, '.', "E."},
        {"glFogxvOES", pnames715, '.', "E."},
        {"glFragmentColorMaterialSGIX", pnames716, '.', "EE"},
        {"glFragmentCoverageColorNV", pnames717, '.', "."},
        {"glFragmentLightModelfSGIX", pnames718, '.', "E."},
        {"glFragmentLightModelfvSGIX", pnames719, '.', "E."},
        {"glFragmentLightModeliSGIX", pnames720, '.', "E."},
        {"glFragmentLightModelivSGIX", pnames721, '.', "E."},
        {"glFragmentLightfSGIX", pnames722, '.', "EE."},
        {"glFragmentLightfvSGIX", pnames723, '.', "EE."},
        {"glFragmentLightiSGIX", pnames724, '.', "EE."},
        {"glFragmentLightivSGIX", pnames725, '.', "EE."},
        {"glFragmentMaterialfSGIX", pnames726, '.', "EE."},
        {"glFragmentMaterialfvSGIX", pnames727, '.', "EE."},
        {"glFragmentMaterialiSGIX", pnames728, '.', "EE."},
        {"glFragmentMaterialivSGIX", pnames729, '.', "EE."},
        {"glFrameTerminatorGREMEDY", pnames730, '.', ""},
        {"glFrameZoomSGIX", pnames731, '.', "."},
        {"glFramebufferDrawBufferEXT", pnames732, '.', ".E"},
        {"glFramebufferDrawBuffersEXT", pnames733, '.', "..."},
        {"glFramebufferParameteri", pnames734, '.', "EE."},
        {"glFramebufferPixelLocalStorageSizeEXT", pnames735, '.', ".."},
        {"glFramebufferReadBufferEXT", pnames736, '.', ".E"},
        {"glFramebufferRenderbuffer", pnames737, '.', "EEE."},
        {"glFramebufferRenderbufferEXT", pnames738, '.', "EEE."},
        {"glFramebufferRenderbufferOES", pnames739, '.', "EEE."},
        {"glFramebufferSampleLocationsfvARB", pnames740, '.', "E..."},
        {"glFramebufferSampleLocationsfvNV", pnames741, '.', "E..."},
        {"glFramebufferSamplePositionsfvAMD", pnames742, '.', "E..."},
        {"glFramebufferTexture", pnames743, '.', "EE.."},
        {"glFramebufferTexture1D", pnames744, '.', "EEE.."},
        {"glFramebufferTexture1DEXT", pnames745, '.', "EEE.."},
        {"glFramebufferTexture2D", pnames746, '.', "EEE.."},
        {"glFramebufferTexture2DEXT", pnames747, '.', "EEE.."},
        {"glFramebufferTexture2DDownsampleIMG", pnames748, '.', "EEE...."},
        {"glFramebufferTexture2DMultisampleEXT", pnames749, '.', "EEE..."},
        {"glFramebufferTexture2DMultisampleIMG", pnames750, '.', "EEE..."},
        {"glFramebufferTexture2DOES", pnames751, '.', "EEE.."},
        {"glFramebufferTexture3D", pnames752, '.', "EEE..."},
        {"glFramebufferTexture3DEXT", pnames753, '.', "EEE..."},
        {"glFramebufferTexture3DOES", pnames754, '.', "EEE..."},
        {"glFramebufferTextureARB", pnames755, '.', "EE.."},
        {"glFramebufferTextureEXT", pnames756, '.', "EE.."},
        {"glFramebufferTextureFaceARB", pnames757, '.', "EE..E"},
        {"glFramebufferTextureFaceEXT", pnames758, '.', "EE..E"},
        {"glFramebufferTextureLayer", pnames759, '.', "EE..."},
        {"glFramebufferTextureLayerARB", pnames760, '.', "EE..."},
        {"glFramebufferTextureLayerEXT", pnames761, '.', "EE..."},
        {"glFramebufferTextureLayerDownsampleIMG", pnames762, '.', "EE....."},
        {"glFramebufferTextureMultisampleMultiviewOVR", pnames763, '.', "EE....."},
        {"glFramebufferTextureMultiviewOVR", pnames764, '.', "EE...."},
        {"glFramebufferTextureOES", pnames765, '.', "EE.."},
        {"glFreeObjectBufferATI", pnames766, '.', "."},
        {"glFrontFace", pnames767, '.', "E"},
        {"glFrustum", pnames768, '.', "......"},
        {"glFrustumf", pnames769, '.', "......"},
        {"glFrustumfOES", pnames770, '.', "......"},
        {"glFrustumx", pnames771, '.', "......"},
        {"glFrustumxOES", pnames772, '.', "......"},
        {"glGenAsyncMarkersSGIX", pnames773, '.', "."},
        {"glGenBuffers", pnames774, '.', ".."},
        {"glGenBuffersARB", pnames775, '.', ".."},
        {"glGenFencesAPPLE", pnames776, '.', ".."},
        {"glGenFencesNV", pnames777, '.', ".."},
        {"glGenFragmentShadersATI", pnames778, '.', "."},
        {"glGenFramebuffers", pnames779, '.', ".."},
        {"glGenFramebuffersEXT", pnames780, '.', ".."},
        {"glGenFramebuffersOES", pnames781, '.', ".."},
        {"glGenLists", pnames782, '.', "."},
        {"glGenNamesAMD", pnames783, '.', "E.."},
        {"glGenOcclusionQueriesNV", pnames784, '.', ".."},
        {"glGenPathsNV", pnames785, '.', "."},
        {"glGenPerfMonitorsAMD", pnames786, '.', ".."},
        {"glGenProgramPipelines", pnames787, '.', ".."},
        {"glGenProgramPipelinesEXT", pnames788, '.', ".."},
        {"glGenProgramsARB", pnames789, '.', ".."},
        {"glGenProgramsNV", pnames790, '.', ".."},
        {"glGenQueries", pnames791, '.', ".."},
        {"glGenQueriesARB", pnames792, '.', ".."},
        {"glGenQueriesEXT", pnames793, '.', ".."},
        {"glGenRenderbuffers", pnames794, '.', ".."},
        {"glGenRenderbuffersEXT", pnames795, '.', ".."},
        {"glGenRenderbuffersOES", pnames796, '.', ".."},
        {"glGenSamplers", pnames797, '.', ".."},
        {"glGenSymbolsEXT", pnames798, '.', "EEE."},
        {"glGenTextures", pnames799, '.', ".."},
        {"glGenTexturesEXT", pnames800, '.', ".."},
        {"glGenTransformFeedbacks", pnames801, '.', ".."},
        {"glGenTransformFeedbacksNV", pnames802, '.', ".."},
        {"glGenVertexArrays", pnames803, '.', ".."},
        {"glGenVertexArraysAPPLE", pnames804, '.', ".."},
        {"glGenVertexArraysOES", pnames805, '.', ".."},
        {"glGenVertexShadersEXT", pnames806, '.', "."},
        {"glGenerateMipmap", pnames807, '.', "E"},
        {"glGenerateMipmapEXT", pnames808, '.', "E"},
        {"glGenerateMipmapOES", pnames809, '.', "E"},
        {"glGenerateMultiTexMipmapEXT", pnames810, '.', "EE"},
        {"glGenerateTextureMipmap", pnames811, '.', "."},
        {"glGenerateTextureMipmapEXT", pnames812, '.', ".E"},
        {"glGetActiveAtomicCounterBufferiv", pnames813, '.', "..E."},
        {"glGetActiveAttrib", pnames814, '.', "......."},
        {"glGetActiveAttribARB", pnames815, '.', "......."},
        {"glGetActiveSubroutineName", pnames816, '.', ".E...."},
        {"glGetActiveSubroutineUniformName", pnames817, '.', ".E...."},
        {"glGetActiveSubroutineUniformiv", pnames818, '.', ".E.E."},
        {"glGetActiveUniform", pnames819, '.', "......."},
        {"glGetActiveUniformARB", pnames820, '.', "......."},
        {"glGetActiveUniformBlockName", pnames821, '.', "....."},
        {"glGetActiveUniformBlockiv", pnames822, '.', "..E."},
        {"glGetActiveUniformName", pnames823, '.', "....."},
        {"glGetActiveUniformsiv", pnames824, '.', "...E."},
        {"glGetActiveVaryingNV", pnames825, '.', "......."},
        {"glGetArrayObjectfvATI", pnames826, '.', "EE."},
        {"glGetArrayObjectivATI", pnames827, '.', "EE."},
        {"glGetAttachedObjectsARB", pnames828, '.', "...."},
        {"glGetAttachedShaders", pnames829, '.', "...."},
        {"glGetAttribLocation", pnames830, '.', ".."},
        {"glGetAttribLocationARB", pnames831, '.', ".."},
        {"glGetBooleanIndexedvEXT", pnames832, '.', "E.."},
        {"glGetBooleani_v", pnames833, '.', "E.."},
        {"glGetBooleanv", pnames834, '.', "E."},
        {"glGetBufferParameteri64v", pnames835, '.', "EE."},
        {"glGetBufferParameteriv", pnames836, '.', "EE."},
        {"glGetBufferParameterivARB", pnames837, '.', "EE."},
        {"glGetBufferParameterui64vNV", pnames838, '.', "EE."},
        {"glGetBufferPointerv", pnames839, '.', "EE."},
        {"glGetBufferPointervARB", pnames840, '.', "EE."},
        {"glGetBufferPointervOES", pnames841, '.', "EE."},
        {"glGetBufferSubData", pnames842, '.', "E..."},
        {"glGetBufferSubDataARB", pnames843, '.', "E..."},
        {"glGetClipPlane", pnames844, '.', "E."},
        {"glGetClipPlanef", pnames845, '.', "E."},
        {"glGetClipPlanefOES", pnames846, '.', "E."},
        {"glGetClipPlanex", pnames847, '.', "E."},
        {"glGetClipPlanexOES", pnames848, '.', "E."},
        {"glGetColorTable", pnames849, '.', "EEE."},
        {"glGetColorTableEXT", pnames850, '.', "EEE."},
        {"glGetColorTableParameterfv", pnames851, '.', "EE."},
        {"glGetColorTableParameterfvEXT", pnames852, '.', "EE."},
        {"glGetColorTableParameterfvSGI", pnames853, '.', "EE."},
        {"glGetColorTableParameteriv", pnames854, '.', "EE."},
        {"glGetColorTableParameterivEXT", pnames855, '.', "EE."},
        {"glGetColorTableParameterivSGI", pnames856, '.', "EE."},
        {"glGetColorTableSGI", pnames857, '.', "EEE."},
        {"glGetCombinerInputParameterfvNV", pnames858, '.', "EEEE."},
        {"glGetCombinerInputParameterivNV", pnames859, '.', "EEEE."},
        {"glGetCombinerOutputParameterfvNV", pnames860, '.', "EEE."},
        {"glGetCombinerOutputParameterivNV", pnames861, '.', "EEE."},
        {"glGetCombinerStageParameterfvNV", pnames862, '.', "EE."},
        {"glGetCommandHeaderNV", pnames863, '.', "E."},
        {"glGetCompressedMultiTexImageEXT", pnames864, '.', "EE.."},
        {"glGetCompressedTexImage", pnames865, '.', "E.."},
        {"glGetCompressedTexImageARB", pnames866, '.', "E.."},
        {"glGetCompressedTextureImage", pnames867, '.', "...."},
        {"glGetCompressedTextureImageEXT", pnames868, '.', ".E.."},
        {"glGetCompressedTextureSubImage", pnames869, '.', ".........."},
        {"glGetConvolutionFilter", pnames870, '.', "EEE."},
        {"glGetConvolutionFilterEXT", pnames871, '.', "EEE."},
        {"glGetConvolutionParameterfv", pnames872, '.', "EE."},
        {"glGetConvolutionParameterfvEXT", pnames873, '.', "EE."},
        {"glGetConvolutionParameteriv", pnames874, '.', "EE."},
        {"glGetConvolutionParameterivEXT", pnames875, '.', "EE."},
        {"glGetConvolutionParameterxvOES", pnames876, '.', "EE."},
        {"glGetCoverageModulationTableNV", pnames877, '.', ".."},
        {"glGetDebugMessageLog", pnames878, '.', "........"},
        {"glGetDebugMessageLogAMD", pnames879, '.', "......."},
        {"glGetDebugMessageLogARB", pnames880, '.', "........"},
        {"glGetDebugMessageLogKHR", pnames881, '.', "........"},
        {"glGetDetailTexFuncSGIS", pnames882, '.', "E."},
        {"glGetDoubleIndexedvEXT", pnames883, '.', "E.."},
        {"glGetDoublei_v", pnames884, '.', "E.."},
        {"glGetDoublei_vEXT", pnames885, '.', "E.."},
        {"glGetDoublev", pnames886, '.', "E."},
        {"glGetDriverControlStringQCOM", pnames887, '.', "...."},
        {"glGetDriverControlsQCOM", pnames888, '.', "..."},
        {"glGetError", pnames889, 'E', ""},
        {"glGetFenceivNV", pnames890, '.', ".E."},
        {"glGetFinalCombinerInputParameterfvNV", pnames891, '.', "EE."},
        {"glGetFinalCombinerInputParameterivNV", pnames892, '.', "EE."},
        {"glGetFirstPerfQueryIdINTEL", pnames893, '.', "."},
        {"glGetFixedv", pnames894, '.', "E."},
        {"glGetFixedvOES", pnames895, '.', "E."},
        {"glGetFloatIndexedvEXT", pnames896, '.', "E.."},
        {"glGetFloati_v", pnames897, '.', "E.."},
        {"glGetFloati_vEXT", pnames898, '.', "E.."},
        {"glGetFloati_vNV", pnames899, '.', "E.."},
        {"glGetFloati_vOES", pnames900, '.', "E.."},
        {"glGetFloatv", pnames901, '.', "E."},
        {"glGetFogFuncSGIS", pnames902, '.', "."},
        {"glGetFragDataIndex", pnames903, '.', ".."},
        {"glGetFragDataIndexEXT", pnames904, '.', ".."},
        {"glGetFragDataLocation", pnames905, '.', ".."},
        {"glGetFragDataLocationEXT", pnames906, '.', ".."},
        {"glGetFragmentLightfvSGIX", pnames907, '.', "EE."},
        {"glGetFragmentLightivSGIX", pnames908, '.', "EE."},
        {"glGetFragmentMaterialfvSGIX", pnames909, '.', "EE."},
        {"glGetFragmentMaterialivSGIX", pnames910, '.', "EE."},
        {"glGetFramebufferAttachmentParameteriv", pnames911, '.', "EEE."},
        {"glGetFramebufferAttachmentParameterivEXT", pnames912, '.', "EEE."},
        {"glGetFramebufferAttachmentParameterivOES", pnames913, '.', "EEE."},
        {"glGetFramebufferParameterfvAMD", pnames914, '.', "EE...."},
        {"glGetFramebufferParameteriv", pnames915, '.', "EE."},
        {"glGetFramebufferParameterivEXT", pnames916, '.', ".E."},
        {"glGetFramebufferPixelLocalStorageSizeEXT", pnames917, '.', "."},
        {"glGetGraphicsResetStatus", pnames918, 'E', ""},
        {"glGetGraphicsResetStatusARB", pnames919, 'E', ""},
        {"glGetGraphicsResetStatusEXT", pnames920, 'E', ""},
        {"glGetGraphicsResetStatusKHR", pnames921, 'E', ""},
        {"glGetHandleARB", pnames922, '.', "E"},
        {"glGetHistogram", pnames923, '.', "EBEE."},
        {"glGetHistogramEXT", pnames924, '.', "EBEE."},
        {"glGetHistogramParameterfv", pnames925, '.', "EE."},
        {"glGetHistogramParameterfvEXT", pnames926, '.', "EE."},
        {"glGetHistogramParameteriv", pnames927, '.', "EE."},
        {"glGetHistogramParameterivEXT", pnames928, '.', "EE."},
        {"glGetHistogramParameterxvOES", pnames929, '.', "EE."},
        {"glGetImageHandleARB", pnames930, '.', "..B.E"},
        {"glGetImageHandleNV", pnames931, '.', "..B.E"},
        {"glGetImageTransformParameterfvHP", pnames932, '.', "EE."},
        {"glGetImageTransformParameterivHP", pnames933, '.', "EE."},
        {"glGetInfoLogARB", pnames934, '.', "...."},
        {"glGetInstrumentsSGIX", pnames935, '.', ""},
        {"glGetInteger64i_v", pnames936, '.', "E.."},
        {"glGetInteger64v", pnames937, '.', "E."},
        {"glGetInteger64vAPPLE", pnames938, '.', "E."},
        {"glGetIntegerIndexedvEXT", pnames939, '.', "E.."},
        {"glGetIntegeri_v", pnames940, '.', "E.."},
        {"glGetIntegeri_vEXT", pnames941, '.', "E.."},
        {"glGetIntegerui64i_vNV", pnames942, '.', "E.."},
        {"glGetIntegerui64vNV", pnames943, '.', "E."},
        {"glGetIntegerv", pnames944, '.', "E."},
        {"glGetInternalformatSampleivNV", pnames945, '.', "EE.E.."},
        {"glGetInternalformati64v", pnames946, '.', "EEE.."},
        {"glGetInternalformativ", pnames947, '.', "EEE.."},
        {"glGetInvariantBooleanvEXT", pnames948, '.', ".E."},
        {"glGetInvariantFloatvEXT", pnames949, '.', ".E."},
        {"glGetInvariantIntegervEXT", pnames950, '.', ".E."},
        {"glGetLightfv", pnames951, '.', "EE."},
        {"glGetLightiv", pnames952, '.', "EE."},
        {"glGetLightxOES", pnames953, '.', "EE."},
        {"glGetLightxv", pnames954, '.', "EE."},
        {"glGetLightxvOES", pnames955, '.', "EE."},
        {"glGetListParameterfvSGIX", pnames956, '.', ".E."},
        {"glGetListParameterivSGIX", pnames957, '.', ".E."},
        {"glGetLocalConstantBooleanvEXT", pnames958, '.', ".E."},
        {"glGetLocalConstantFloatvEXT", pnames959, '.', ".E."},
        {"glGetLocalConstantIntegervEXT", pnames960, '.', ".E."},
        {"glGetMapAttribParameterfvNV", pnames961, '.', "E.E."},
        {"glGetMapAttribParameterivNV", pnames962, '.', "E.E."},
        {"glGetMapControlPointsNV", pnames963, '.', "E.E..B."},
        {"glGetMapParameterfvNV", pnames964, '.', "EE."},
        {"glGetMapParameterivNV", pnames965, '.', "EE."},
        {"glGetMapdv", pnames966, '.', "EE."},
        {"glGetMapfv", pnames967, '.', "EE."},
        {"glGetMapiv", pnames968, '.', "EE."},
        {"glGetMapxvOES", pnames969, '.', "EE."},
        {"glGetMaterialfv", pnames970, '.', "EE."},
        {"glGetMaterialiv", pnames971, '.', "EE."},
        {"glGetMaterialxOES", pnames972, '.', "EE."},
        {"glGetMaterialxv", pnames973, '.', "EE."},
        {"glGetMaterialxvOES", pnames974, '.', "EE."},
        {"glGetMinmax", pnames975, '.', "EBEE."},
        {"glGetMinmaxEXT", pnames976, '.', "EBEE."},
        {"glGetMinmaxParameterfv", pnames977, '.', "EE."},
        {"glGetMinmaxParameterfvEXT", pnames978, '.', "EE."},
        {"glGetMinmaxParameteriv", pnames979, '.', "EE."},
        {"glGetMinmaxParameterivEXT", pnames980, '.', "EE."},
        {"glGetMultiTexEnvfvEXT", pnames981, '.', "EEE."},
        {"glGetMultiTexEnvivEXT", pnames982, '.', "EEE."},
        {"glGetMultiTexGendvEXT", pnames983, '.', "EEE."},
        {"glGetMultiTexGenfvEXT", pnames984, '.', "EEE."},
        {"glGetMultiTexGenivEXT", pnames985, '.', "EEE."},
        {"glGetMultiTexImageEXT", pnames986, '.', "EE.EE."},
        {"glGetMultiTexLevelParameterfvEXT", pnames987, '.', "EE.E."},
        {"glGetMultiTexLevelParameterivEXT", pnames988, '.', "EE.E."},
        {"glGetMultiTexParameterIivEXT", pnames989, '.', "EEE."},
        {"glGetMultiTexParameterIuivEXT", pnames990, '.', "EEE."},
        {"glGetMultiTexParameterfvEXT", pnames991, '.', "EEE."},
        {"glGetMultiTexParameterivEXT", pnames992, '.', "EEE."},
        {"glGetMultisamplefv", pnames993, '.', "E.."},
        {"glGetMultisamplefvNV", pnames994, '.', "E.."},
        {"glGetNamedBufferParameteri64v", pnames995, '.', ".E."},
        {"glGetNamedBufferParameteriv", pnames996, '.', ".E."},
        {"glGetNamedBufferParameterivEXT", pnames997, '.', ".E."},
        {"glGetNamedBufferParameterui64vNV", pnames998, '.', ".E."},
        {"glGetNamedBufferPointerv", pnames999, '.', ".E."},
        {"glGetNamedBufferPointervEXT", pnames1000, '.', ".E."},
        {"glGetNamedBufferSubData", pnames1001, '.', "...."},
        {"glGetNamedBufferSubDataEXT", pnames1002, '.', "...."},
        {"glGetNamedFramebufferParameterfvAMD", pnames1003, '.', "EE...."},
        {"glGetNamedFramebufferAttachmentParameteriv", pnames1004, '.', ".EE."},
        {"glGetNamedFramebufferAttachmentParameterivEXT", pnames1005, '.', ".EE."},
        {"glGetNamedFramebufferParameteriv", pnames1006, '.', ".E."},
        {"glGetNamedFramebufferParameterivEXT", pnames1007, '.', ".E."},
        {"glGetNamedProgramLocalParameterIivEXT", pnames1008, '.', ".E.."},
        {"glGetNamedProgramLocalParameterIuivEXT", pnames1009, '.', ".E.."},
        {"glGetNamedProgramLocalParameterdvEXT", pnames1010, '.', ".E.."},
        {"glGetNamedProgramLocalParameterfvEXT", pnames1011, '.', ".E.."},
        {"glGetNamedProgramStringEXT", pnames1012, '.', ".EE."},
        {"glGetNamedProgramivEXT", pnames1013, '.', ".EE."},
        {"glGetNamedRenderbufferParameteriv", pnames1014, '.', ".E."},
        {"glGetNamedRenderbufferParameterivEXT", pnames1015, '.', ".E."},
        {"glGetNamedStringARB", pnames1016, '.', "....."},
        {"glGetNamedStringivARB", pnames1017, '.', "..E."},
        {"glGetNextPerfQueryIdINTEL", pnames1018, '.', ".."},
        {"glGetObjectBufferfvATI", pnames1019, '.', ".E."},
        {"glGetObjectBufferivATI", pnames1020, '.', ".E."},
        {"glGetObjectLabel", pnames1021, '.', "E...."},
        {"glGetObjectLabelEXT", pnames1022, '.', "E...."},
        {"glGetObjectLabelKHR", pnames1023, '.', "E...."},
        {"glGetObjectParameterfvARB", pnames1024, '.', ".E."},
        {"glGetObjectParameterivAPPLE", pnames1025, '.', "E.E."},
        {"glGetObjectParameterivARB", pnames1026, '.', ".E."},
        {"glGetObjectPtrLabel", pnames1027, '.', "...."},
        {"glGetObjectPtrLabelKHR", pnames1028, '.', "...."},
        {"glGetOcclusionQueryivNV", pnames1029, '.', ".E."},
        {"glGetOcclusionQueryuivNV", pnames1030, '.', ".E."},
        {"glGetPathColorGenfvNV", pnames1031, '.', "EE."},
        {"glGetPathColorGenivNV", pnames1032, '.', "EE."},
        {"glGetPathCommandsNV", pnames1033, '.', ".."},
        {"glGetPathCoordsNV", pnames1034, '.', ".."},
        {"glGetPathDashArrayNV", pnames1035, '.', ".."},
        {"glGetPathLengthNV", pnames1036, '.', "..."},
        {"glGetPathMetricRangeNV", pnames1037, '.', "F...."},
        {"glGetPathMetricsNV", pnames1038, '.', "F.E...."},
        {"glGetPathParameterfvNV", pnames1039, '.', ".E."},
        {"glGetPathParameterivNV", pnames1040, '.', ".E."},
        {"glGetPathSpacingNV", pnames1041, '.', "E.E....E."},
        {"glGetPathTexGenfvNV", pnames1042, '.', "EE."},
        {"glGetPathTexGenivNV", pnames1043, '.', "EE."},
        {"glGetPerfCounterInfoINTEL", pnames1044, '.', "..........."},
        {"glGetPerfMonitorCounterDataAMD", pnames1045, '.', ".E..."},
        {"glGetPerfMonitorCounterInfoAMD", pnames1046, '.', "..E."},
        {"glGetPerfMonitorCounterStringAMD", pnames1047, '.', "....."},
        {"glGetPerfMonitorCountersAMD", pnames1048, '.', "....."},
        {"glGetPerfMonitorGroupStringAMD", pnames1049, '.', "...."},
        {"glGetPerfMonitorGroupsAMD", pnames1050, '.', "..."},
        {"glGetPerfQueryDataINTEL", pnames1051, '.', "....."},
        {"glGetPerfQueryIdByNameINTEL", pnames1052, '.', ".."},
        {"glGetPerfQueryInfoINTEL", pnames1053, '.', "......."},
        {"glGetPixelMapfv", pnames1054, '.', "E."},
        {"glGetPixelMapuiv", pnames1055, '.', "E."},
        {"glGetPixelMapusv", pnames1056, '.', "E."},
        {"glGetPixelMapxv", pnames1057, '.', "E.."},
        {"glGetPixelTexGenParameterfvSGIS", pnames1058, '.', "E."},
        {"glGetPixelTexGenParameterivSGIS", pnames1059, '.', "E."},
        {"glGetPixelTransformParameterfvEXT", pnames1060, '.', "EE."},
        {"glGetPixelTransformParameterivEXT", pnames1061, '.', "EE."},
        {"glGetPointerIndexedvEXT", pnames1062, '.', "E.."},
        {"glGetPointeri_vEXT", pnames1063, '.', "E.."},
        {"glGetPointerv", pnames1064, '.', "E."},
        {"glGetPointervEXT", pnames1065, '.', "E."},
        {"glGetPointervKHR", pnames1066, '.', "E."},
        {"glGetPolygonStipple", pnames1067, '.', "."},
        {"glGetProgramBinary", pnames1068, '.', "....."},
        {"glGetProgramBinaryOES", pnames1069, '.', "....."},
        {"glGetProgramEnvParameterIivNV", pnames1070, '.', "E.."},
        {"glGetProgramEnvParameterIuivNV", pnames1071, '.', "E.."},
        {"glGetProgramEnvParameterdvARB", pnames1072, '.', "E.."},
        {"glGetProgramEnvParameterfvARB", pnames1073, '.', "E.."},
        {"glGetProgramInfoLog", pnames1074, '.', "...."},
        {"glGetProgramInterfaceiv", pnames1075, '.', ".EE."},
        {"glGetProgramLocalParameterIivNV", pnames1076, '.', "E.."},
        {"glGetProgramLocalParameterIuivNV", pnames1077, '.', "E.."},
        {"glGetProgramLocalParameterdvARB", pnames1078, '.', "E.."},
        {"glGetProgramLocalParameterfvARB", pnames1079, '.', "E.."},
        {"glGetProgramNamedParameterdvNV", pnames1080, '.', "...."},
        {"glGetProgramNamedParameterfvNV", pnames1081, '.', "...."},
        {"glGetProgramParameterdvNV", pnames1082, '.', "E.E."},
        {"glGetProgramParameterfvNV", pnames1083, '.', "E.E."},
        {"glGetProgramPipelineInfoLog", pnames1084, '.', "...."},
        {"glGetProgramPipelineInfoLogEXT", pnames1085, '.', "...."},
        {"glGetProgramPipelineiv", pnames1086, '.', ".E."},
        {"glGetProgramPipelineivEXT", pnames1087, '.', ".E."},
        {"glGetProgramResourceIndex", pnames1088, '.', ".E."},
        {"glGetProgramResourceLocation", pnames1089, '.', ".E."},
        {"glGetProgramResourceLocationIndex", pnames1090, '.', ".E."},
        {"glGetProgramResourceLocationIndexEXT", pnames1091, '.', ".E."},
        {"glGetProgramResourceName", pnames1092, '.', ".E...."},
        {"glGetProgramResourcefvNV", pnames1093, '.', ".E......"},
        {"glGetProgramResourceiv", pnames1094, '.', ".E......"},
        {"glGetProgramStageiv", pnames1095, '.', ".EE."},
        {"glGetProgramStringARB", pnames1096, '.', "EE."},
        {"glGetProgramStringNV", pnames1097, '.', ".E."},
        {"glGetProgramSubroutineParameteruivNV", pnames1098, '.', "E.."},
        {"glGetProgramiv", pnames1099, '.', ".E."},
        {"glGetProgramivARB", pnames1100, '.', "EE."},
        {"glGetProgramivNV", pnames1101, '.', ".E."},
        {"glGetQueryBufferObjecti64v", pnames1102, '.', "..E."},
        {"glGetQueryBufferObjectiv", pnames1103, '.', "..E."},
        {"glGetQueryBufferObjectui64v", pnames1104, '.', "..E."},
        {"glGetQueryBufferObjectuiv", pnames1105, '.', "..E."},
        {"glGetQueryIndexediv", pnames1106, '.', "E.E."},
        {"glGetQueryObjecti64v", pnames1107, '.', ".E."},
        {"glGetQueryObjecti64vEXT", pnames1108, '.', ".E."},
        {"glGetQueryObjectiv", pnames1109, '.', ".E."},
        {"glGetQueryObjectivARB", pnames1110, '.', ".E."},
        {"glGetQueryObjectivEXT", pnames1111, '.', ".E."},
        {"glGetQueryObjectui64v", pnames1112, '.', ".E."},
        {"glGetQueryObjectui64vEXT", pnames1113, '.', ".E."},
        {"glGetQueryObjectuiv", pnames1114, '.', ".E."},
        {"glGetQueryObjectuivARB", pnames1115, '.', ".E."},
        {"glGetQueryObjectuivEXT", pnames1116, '.', ".E."},
        {"glGetQueryiv", pnames1117, '.', "EE."},
        {"glGetQueryivARB", pnames1118, '.', "EE."},
        {"glGetQueryivEXT", pnames1119, '.', "EE."},
        {"glGetRenderbufferParameteriv", pnames1120, '.', "EE."},
        {"glGetRenderbufferParameterivEXT", pnames1121, '.', "EE."},
        {"glGetRenderbufferParameterivOES", pnames1122, '.', "EE."},
        {"glGetSamplerParameterIiv", pnames1123, '.', ".E."},
        {"glGetSamplerParameterIivEXT", pnames1124, '.', ".E."},
        {"glGetSamplerParameterIivOES", pnames1125, '.', ".E."},
        {"glGetSamplerParameterIuiv", pnames1126, '.', ".E."},
        {"glGetSamplerParameterIuivEXT", pnames1127, '.', ".E."},
        {"glGetSamplerParameterIuivOES", pnames1128, '.', ".E."},
        {"glGetSamplerParameterfv", pnames1129, '.', ".E."},
        {"glGetSamplerParameteriv", pnames1130, '.', ".E."},
        {"glGetSeparableFilter", pnames1131, '.', "EEE..."},
        {"glGetSeparableFilterEXT", pnames1132, '.', "EEE..."},
        {"glGetShaderInfoLog", pnames1133, '.', "...."},
        {"glGetShaderPrecisionFormat", pnames1134, '.', "EE.."},
        {"glGetShaderSource", pnames1135, '.', "...."},
        {"glGetShaderSourceARB", pnames1136, '.', "...."},
        {"glGetShaderiv", pnames1137, '.', ".E."},
        {"glGetSharpenTexFuncSGIS", pnames1138, '.', "E."},
        {"glGetStageIndexNV", pnames1139, '.', "E"},
        {"glGetString", pnames1140, '.', "E"},
        {"glGetStringi", pnames1141, '.', "E."},
        {"glGetSubroutineIndex", pnames1142, '.', ".E."},
        {"glGetSubroutineUniformLocation", pnames1143, '.', ".E."},
        {"glGetSynciv", pnames1144, '.', ".E..."},
        {"glGetSyncivAPPLE", pnames1145, '.', ".E..."},
        {"glGetTexBumpParameterfvATI", pnames1146, '.', "E."},
        {"glGetTexBumpParameterivATI", pnames1147, '.', "E."},
        {"glGetTexEnvfv", pnames1148, '.', "EE."},
        {"glGetTexEnviv", pnames1149, '.', "EE."},
        {"glGetTexEnvxv", pnames1150, '.', "EE."},
        {"glGetTexEnvxvOES", pnames1151, '.', "EE."},
        {"glGetTexFilterFuncSGIS", pnames1152, '.', "EE."},
        {"glGetTexGendv", pnames1153, '.', "EE."},
        {"glGetTexGenfv", pnames1154, '.', "EE."},
        {"glGetTexGenfvOES", pnames1155, '.', "EE."},
        {"glGetTexGeniv", pnames1156, '.', "EE."},
        {"glGetTexGenivOES", pnames1157, '.', "EE."},
        {"glGetTexGenxvOES", pnames1158, '.', "EE."},
        {"glGetTexImage", pnames1159, '.', "E.EE."},
        {"glGetTexLevelParameterfv", pnames1160, '.', "E.E."},
        {"glGetTexLevelParameteriv", pnames1161, '.', "E.E."},
        {"glGetTexLevelParameterxvOES", pnames1162, '.', "E.E."},
        {"glGetTexParameterIiv", pnames1163, '.', "EE."},
        {"glGetTexParameterIivEXT", pnames1164, '.', "EE."},
        {"glGetTexParameterIivOES", pnames1165, '.', "EE."},
        {"glGetTexParameterIuiv", pnames1166, '.', "EE."},
        {"glGetTexParameterIuivEXT", pnames1167, '.', "EE."},
        {"glGetTexParameterIuivOES", pnames1168, '.', "EE."},
        {"glGetTexParameterPointervAPPLE", pnames1169, '.', "EE."},
        {"glGetTexParameterfv", pnames1170, '.', "EE."},
        {"glGetTexParameteriv", pnames1171, '.', "EE."},
        {"glGetTexParameterxv", pnames1172, '.', "EE."},
        {"glGetTexParameterxvOES", pnames1173, '.', "EE."},
        {"glGetTextureHandleARB", pnames1174, '.', "."},
        {"glGetTextureHandleIMG", pnames1175, '.', "."},
        {"glGetTextureHandleNV", pnames1176, '.', "."},
        {"glGetTextureImage", pnames1177, '.', "..EE.."},
        {"glGetTextureImageEXT", pnames1178, '.', ".E.EE."},
        {"glGetTextureLevelParameterfv", pnames1179, '.', "..E."},
        {"glGetTextureLevelParameterfvEXT", pnames1180, '.', ".E.E."},
        {"glGetTextureLevelParameteriv", pnames1181, '.', "..E."},
        {"glGetTextureLevelParameterivEXT", pnames1182, '.', ".E.E."},
        {"glGetTextureParameterIiv", pnames1183, '.', ".E."},
        {"glGetTextureParameterIivEXT", pnames1184, '.', ".EE."},
        {"glGetTextureParameterIuiv", pnames1185, '.', ".E."},
        {"glGetTextureParameterIuivEXT", pnames1186, '.', ".EE."},
        {"glGetTextureParameterfv", pnames1187, '.', ".E."},
        {"glGetTextureParameterfvEXT", pnames1188, '.', ".EE."},
        {"glGetTextureParameteriv", pnames1189, '.', ".E."},
        {"glGetTextureParameterivEXT", pnames1190, '.', ".EE."},
        {"glGetTextureSamplerHandleARB", pnames1191, '.', ".."},
        {"glGetTextureSamplerHandleIMG", pnames1192, '.', ".."},
        {"glGetTextureSamplerHandleNV", pnames1193, '.', ".."},
        {"glGetTextureSubImage", pnames1194, '.', "........EE.."},
        {"glGetTrackMatrixivNV", pnames1195, '.', "E.E."},
        {"glGetTransformFeedbackVarying", pnames1196, '.', "......."},
        {"glGetTransformFeedbackVaryingEXT", pnames1197, '.', "......."},
        {"glGetTransformFeedbackVaryingNV", pnames1198, '.', "..."},
        {"glGetTransformFeedbacki64_v", pnames1199, '.', ".E.."},
        {"glGetTransformFeedbacki_v", pnames1200, '.', ".E.."},
        {"glGetTransformFeedbackiv", pnames1201, '.', ".E."},
        {"glGetTranslatedShaderSourceANGLE", pnames1202, '.', "...."},
        {"glGetUniformBlockIndex", pnames1203, '.', ".."},
        {"glGetUniformBufferSizeEXT", pnames1204, '.', ".."},
        {"glGetUniformIndices", pnames1205, '.', "...."},
        {"glGetUniformLocation", pnames1206, '.', ".."},
        {"glGetUniformLocationARB", pnames1207, '.', ".."},
        {"glGetUniformOffsetEXT", pnames1208, '.', ".."},
        {"glGetUniformSubroutineuiv", pnames1209, '.', "E.."},
        {"glGetUniformdv", pnames1210, '.', "..."},
        {"glGetUniformfv", pnames1211, '.', "..."},
        {"glGetUniformfvARB", pnames1212, '.', "..."},
        {"glGetUniformi64vARB", pnames1213, '.', "..."},
        {"glGetUniformi64vNV", pnames1214, '.', "..."},
        {"glGetUniformiv", pnames1215, '.', "..."},
        {"glGetUniformivARB", pnames1216, '.', "..."},
        {"glGetUniformui64vARB", pnames1217, '.', "..."},
        {"glGetUniformui64vNV", pnames1218, '.', "..."},
        {"glGetUniformuiv", pnames1219, '.', "..."},
        {"glGetUniformuivEXT", pnames1220, '.', "..."},
        {"glGetVariantArrayObjectfvATI", pnames1221, '.', ".E."},
        {"glGetVariantArrayObjectivATI", pnames1222, '.', ".E."},
        {"glGetVariantBooleanvEXT", pnames1223, '.', ".E."},
        {"glGetVariantFloatvEXT", pnames1224, '.', ".E."},
        {"glGetVariantIntegervEXT", pnames1225, '.', ".E."},
        {"glGetVariantPointervEXT", pnames1226, '.', ".E."},
        {"glGetVaryingLocationNV", pnames1227, '.', ".."},
        {"glGetVertexArrayIndexed64iv", pnames1228, '.', "..E."},
        {"glGetVertexArrayIndexediv", pnames1229, '.', "..E."},
        {"glGetVertexArrayIntegeri_vEXT", pnames1230, '.', "..E."},
        {"glGetVertexArrayIntegervEXT", pnames1231, '.', ".E."},
        {"glGetVertexArrayPointeri_vEXT", pnames1232, '.', "..E."},
        {"glGetVertexArrayPointervEXT", pnames1233, '.', ".E."},
        {"glGetVertexArrayiv", pnames1234, '.', ".E."},
        {"glGetVertexAttribArrayObjectfvATI", pnames1235, '.', ".E."},
        {"glGetVertexAttribArrayObjectivATI", pnames1236, '.', ".E."},
        {"glGetVertexAttribIiv", pnames1237, '.', ".E."},
        {"glGetVertexAttribIivEXT", pnames1238, '.', ".E."},
        {"glGetVertexAttribIuiv", pnames1239, '.', ".E."},
        {"glGetVertexAttribIuivEXT", pnames1240, '.', ".E."},
        {"glGetVertexAttribLdv", pnames1241, '.', ".E."},
        {"glGetVertexAttribLdvEXT", pnames1242, '.', ".E."},
        {"glGetVertexAttribLi64vNV", pnames1243, '.', ".E."},
        {"glGetVertexAttribLui64vARB", pnames1244, '.', ".E."},
        {"glGetVertexAttribLui64vNV", pnames1245, '.', ".E."},
        {"glGetVertexAttribPointerv", pnames1246, '.', ".E."},
        {"glGetVertexAttribPointervARB", pnames1247, '.', ".E."},
        {"glGetVertexAttribPointervNV", pnames1248, '.', ".E."},
        {"glGetVertexAttribdv", pnames1249, '.', ".E."},
        {"glGetVertexAttribdvARB", pnames1250, '.', ".E."},
        {"glGetVertexAttribdvNV", pnames1251, '.', ".E."},
        {"glGetVertexAttribfv", pnames1252, '.', ".E."},
        {"glGetVertexAttribfvARB", pnames1253, '.', ".E."},
        {"glGetVertexAttribfvNV", pnames1254, '.', ".E."},
        {"glGetVertexAttribiv", pnames1255, '.', ".E."},
        {"glGetVertexAttribivARB", pnames1256, '.', ".E."},
        {"glGetVertexAttribivNV", pnames1257, '.', ".E."},
        {"glGetVideoCaptureStreamdvNV", pnames1258, '.', "..E."},
        {"glGetVideoCaptureStreamfvNV", pnames1259, '.', "..E."},
        {"glGetVideoCaptureStreamivNV", pnames1260, '.', "..E."},
        {"glGetVideoCaptureivNV", pnames1261, '.', ".E."},
        {"glGetVideoi64vNV", pnames1262, '.', ".E."},
        {"glGetVideoivNV", pnames1263, '.', ".E."},
        {"glGetVideoui64vNV", pnames1264, '.', ".E."},
        {"glGetVideouivNV", pnames1265, '.', ".E."},
        {"glGetnColorTable", pnames1266, '.', "EEE.."},
        {"glGetnColorTableARB", pnames1267, '.', "EEE.."},
        {"glGetnCompressedTexImage", pnames1268, '.', "E..."},
        {"glGetnCompressedTexImageARB", pnames1269, '.', "E..."},
        {"glGetnConvolutionFilter", pnames1270, '.', "EEE.."},
        {"glGetnConvolutionFilterARB", pnames1271, '.', "EEE.."},
        {"glGetnHistogram", pnames1272, '.', "EBEE.."},
        {"glGetnHistogramARB", pnames1273, '.', "EBEE.."},
        {"glGetnMapdv", pnames1274, '.', "EE.."},
        {"glGetnMapdvARB", pnames1275, '.', "EE.."},
        {"glGetnMapfv", pnames1276, '.', "EE.."},
        {"glGetnMapfvARB", pnames1277, '.', "EE.."},
        {"glGetnMapiv", pnames1278, '.', "EE.."},
        {"glGetnMapivARB", pnames1279, '.', "EE.."},
        {"glGetnMinmax", pnames1280, '.', "EBEE.."},
        {"glGetnMinmaxARB", pnames1281, '.', "EBEE.."},
        {"glGetnPixelMapfv", pnames1282, '.', "E.."},
        {"glGetnPixelMapfvARB", pnames1283, '.', "E.."},
        {"glGetnPixelMapuiv", pnames1284, '.', "E.."},
        {"glGetnPixelMapuivARB", pnames1285, '.', "E.."},
        {"glGetnPixelMapusv", pnames1286, '.', "E.."},
        {"glGetnPixelMapusvARB", pnames1287, '.', "E.."},
        {"glGetnPolygonStipple", pnames1288, '.', ".."},
        {"glGetnPolygonStippleARB", pnames1289, '.', ".."},
        {"glGetnSeparableFilter", pnames1290, '.', "EEE....."},
        {"glGetnSeparableFilterARB", pnames1291, '.', "EEE....."},
        {"glGetnTexImage", pnames1292, '.', "E.EE.."},
        {"glGetnTexImageARB", pnames1293, '.', "E.EE.."},
        {"glGetnUniformdv", pnames1294, '.', "...."},
        {"glGetnUniformdvARB", pnames1295, '.', "...."},
        {"glGetnUniformfv", pnames1296, '.', "...."},
        {"glGetnUniformfvARB", pnames1297, '.', "...."},
        {"glGetnUniformfvEXT", pnames1298, '.', "...."},
        {"glGetnUniformfvKHR", pnames1299, '.', "...."},
        {"glGetnUniformi64vARB", pnames1300, '.', "...."},
        {"glGetnUniformiv", pnames1301, '.', "...."},
        {"glGetnUniformivARB", pnames1302, '.', "...."},
        {"glGetnUniformivEXT", pnames1303, '.', "...."},
        {"glGetnUniformivKHR", pnames1304, '.', "...."},
        {"glGetnUniformui64vARB", pnames1305, '.', "...."},
        {"glGetnUniformuiv", pnames1306, '.', "...."},
        {"glGetnUniformuivARB", pnames1307, '.', "...."},
        {"glGetnUniformuivKHR", pnames1308, '.', "...."},
        {"glGlobalAlphaFactorbSUN", pnames1309, '.', "."},
        {"glGlobalAlphaFactordSUN", pnames1310, '.', "."},
        {"glGlobalAlphaFactorfSUN", pnames1311, '.', "."},
        {"glGlobalAlphaFactoriSUN", pnames1312, '.', "."},
        {"glGlobalAlphaFactorsSUN", pnames1313, '.', "."},
        {"glGlobalAlphaFactorubSUN", pnames1314, '.', "."},
        {"glGlobalAlphaFactoruiSUN", pnames1315, '.', "."},
        {"glGlobalAlphaFactorusSUN", pnames1316, '.', "."},
        {"glHint", pnames1317, '.', "EE"},
        {"glHintPGI", pnames1318, '.', "E."},
        {"glHistogram", pnames1319, '.', "E.EB"},
        {"glHistogramEXT", pnames1320, '.', "E.EB"},
        {"glIglooInterfaceSGIX", pnames1321, '.', "E."},
        {"glImageTransformParameterfHP", pnames1322, '.', "EE."},
        {"glImageTransformParameterfvHP", pnames1323, '.', "EE."},
        {"glImageTransformParameteriHP", pnames1324, '.', "EE."},
        {"glImageTransformParameterivHP", pnames1325, '.', "EE."},
        {"glImportSyncEXT", pnames1326, '.', "E.F"},
        {"glIndexFormatNV", pnames1327, '.', "E."},
        {"glIndexFuncEXT", pnames1328, '.', "E."},
        {"glIndexMask", pnames1329, '.', "."},
        {"glIndexMaterialEXT", pnames1330, '.', "EE"},
        {"glIndexPointer", pnames1331, '.', "E.."},
        {"glIndexPointerEXT", pnames1332, '.', "E..."},
        {"glIndexPointerListIBM", pnames1333, '.', "E..."},
        {"glIndexd", pnames1334, '.', "."},
        {"glIndexdv", pnames1335, '.', "."},
        {"glIndexf", pnames1336, '.', "."},
        {"glIndexfv", pnames1337, '.', "."},
        {"glIndexi", pnames1338, '.', "."},
        {"glIndexiv", pnames1339, '.', "."},
        {"glIndexs", pnames1340, '.', "."},
        {"glIndexsv", pnames1341, '.', "."},
        {"glIndexub", pnames1342, '.', "."},
        {"glIndexubv", pnames1343, '.', "."},
        {"glIndexxOES", pnames1344, '.', "."},
        {"glIndexxvOES", pnames1345, '.', "."},
        {"glInitNames", pnames1346, '.', ""},
        {"glInsertComponentEXT", pnames1347, '.', "..."},
        {"glInsertEventMarkerEXT", pnames1348, '.', ".."},
        {"glInstrumentsBufferSGIX", pnames1349, '.', ".."},
        {"glInterleavedArrays", pnames1350, '.', "E.."},
        {"glInterpolatePathsNV", pnames1351, '.', "...."},
        {"glInvalidateBufferData", pnames1352, '.', "."},
        {"glInvalidateBufferSubData", pnames1353, '.', "..."},
        {"glInvalidateFramebuffer", pnames1354, '.', "E.."},
        {"glInvalidateNamedFramebufferData", pnames1355, '.', "..."},
        {"glInvalidateNamedFramebufferSubData", pnames1356, '.', "......."},
        {"glInvalidateSubFramebuffer", pnames1357, '.', "E......"},
        {"glInvalidateTexImage", pnames1358, '.', ".."},
        {"glInvalidateTexSubImage", pnames1359, '.', "........"},
        {"glIsAsyncMarkerSGIX", pnames1360, 'B', "."},
        {"glIsBuffer", pnames1361, 'B', "."},
        {"glIsBufferARB", pnames1362, 'B', "."},
        {"glIsBufferResidentNV", pnames1363, 'B', "E"},
        {"glIsCommandListNV", pnames1364, 'B', "."},
        {"glIsEnabled", pnames1365, 'B', "E"},
        {"glIsEnabledIndexedEXT", pnames1366, 'B', "E."},
        {"glIsEnabledi", pnames1367, 'B', "E."},
        {"glIsEnablediEXT", pnames1368, 'B', "E."},
        {"glIsEnablediNV", pnames1369, 'B', "E."},
        {"glIsEnablediOES", pnames1370, 'B', "E."},
        {"glIsFenceAPPLE", pnames1371, 'B', "."},
        {"glIsFenceNV", pnames1372, 'B', "."},
        {"glIsFramebuffer", pnames1373, 'B', "."},
        {"glIsFramebufferEXT", pnames1374, 'B', "."},
        {"glIsFramebufferOES", pnames1375, 'B', "."},
        {"glIsImageHandleResidentARB", pnames1376, 'B', "."},
        {"glIsImageHandleResidentNV", pnames1377, 'B', "."},
        {"glIsList", pnames1378, 'B', "."},
        {"glIsNameAMD", pnames1379, 'B', "E."},
        {"glIsNamedBufferResidentNV", pnames1380, 'B', "."},
        {"glIsNamedStringARB", pnames1381, 'B', ".."},
        {"glIsObjectBufferATI", pnames1382, 'B', "."},
        {"glIsOcclusionQueryNV", pnames1383, 'B', "."},
        {"glIsPathNV", pnames1384, 'B', "."},
        {"glIsPointInFillPathNV", pnames1385, 'B', "...."},
        {"glIsPointInStrokePathNV", pnames1386, 'B', "..."},
        {"glIsProgram", pnames1387, 'B', "."},
        {"glIsProgramARB", pnames1388, 'B', "."},
        {"glIsProgramNV", pnames1389, 'B', "."},
        {"glIsProgramPipeline", pnames1390, 'B', "."},
        {"glIsProgramPipelineEXT", pnames1391, 'B', "."},
        {"glIsQuery", pnames1392, 'B', "."},
        {"glIsQueryARB", pnames1393, 'B', "."},
        {"glIsQueryEXT", pnames1394, 'B', "."},
        {"glIsRenderbuffer", pnames1395, 'B', "."},
        {"glIsRenderbufferEXT", pnames1396, 'B', "."},
        {"glIsRenderbufferOES", pnames1397, 'B', "."},
        {"glIsSampler", pnames1398, 'B', "."},
        {"glIsShader", pnames1399, 'B', "."},
        {"glIsStateNV", pnames1400, 'B', "."},
        {"glIsSync", pnames1401, 'B', "."},
        {"glIsSyncAPPLE", pnames1402, 'B', "."},
        {"glIsTexture", pnames1403, 'B', "."},
        {"glIsTextureEXT", pnames1404, 'B', "."},
        {"glIsTextureHandleResidentARB", pnames1405, 'B', "."},
        {"glIsTextureHandleResidentNV", pnames1406, 'B', "."},
        {"glIsTransformFeedback", pnames1407, 'B', "."},
        {"glIsTransformFeedbackNV", pnames1408, 'B', "."},
        {"glIsVariantEnabledEXT", pnames1409, 'B', ".E"},
        {"glIsVertexArray", pnames1410, 'B', "."},
        {"glIsVertexArrayAPPLE", pnames1411, 'B', "."},
        {"glIsVertexArrayOES", pnames1412, 'B', "."},
        {"glIsVertexAttribEnabledAPPLE", pnames1413, 'B', ".E"},
        {"glLabelObjectEXT", pnames1414, '.', "E..."},
        {"glLightEnviSGIX", pnames1415, '.', "E."},
        {"glLightModelf", pnames1416, '.', "E."},
        {"glLightModelfv", pnames1417, '.', "E."},
        {"glLightModeli", pnames1418, '.', "E."},
        {"glLightModeliv", pnames1419, '.', "E."},
        {"glLightModelx", pnames1420, '.', "E."},
        {"glLightModelxOES", pnames1421, '.', "E."},
        {"glLightModelxv", pnames1422, '.', "E."},
        {"glLightModelxvOES", pnames1423, '.', "E."},
        {"glLightf", pnames1424, '.', "EE."},
        {"glLightfv", pnames1425, '.', "EE."},
        {"glLighti", pnames1426, '.', "EE."},
        {"glLightiv", pnames1427, '.', "EE."},
        {"glLightx", pnames1428, '.', "EE."},
        {"glLightxOES", pnames1429, '.', "EE."},
        {"glLightxv", pnames1430, '.', "EE."},
        {"glLightxvOES", pnames1431, '.', "EE."},
        {"glLineStipple", pnames1432, '.', ".."},
        {"glLineWidth", pnames1433, '.', "."},
        {"glLineWidthx", pnames1434, '.', "."},
        {"glLineWidthxOES", pnames1435, '.', "."},
        {"glLinkProgram", pnames1436, '.', "."},
        {"glLinkProgramARB", pnames1437, '.', "."},
        {"glListBase", pnames1438, '.', "."},
        {"glListDrawCommandsStatesClientNV", pnames1439, '.', "......."},
        {"glListParameterfSGIX", pnames1440, '.', ".E."},
        {"glListParameterfvSGIX", pnames1441, '.', ".E."},
        {"glListParameteriSGIX", pnames1442, '.', ".E."},
        {"glListParameterivSGIX", pnames1443, '.', ".E."},
        {"glLoadIdentity", pnames1444, '.', ""},
        {"glLoadIdentityDeformationMapSGIX", pnames1445, '.', "F"},
        {"glLoadMatrixd", pnames1446, '.', "."},
        {"glLoadMatrixf", pnames1447, '.', "."},
        {"glLoadMatrixx", pnames1448, '.', "."},
        {"glLoadMatrixxOES", pnames1449, '.', "."},
        {"glLoadName", pnames1450, '.', "."},
        {"glLoadPaletteFromModelViewMatrixOES", pnames1451, '.', ""},
        {"glLoadProgramNV", pnames1452, '.', "E..."},
        {"glLoadTransposeMatrixd", pnames1453, '.', "."},
        {"glLoadTransposeMatrixdARB", pnames1454, '.', "."},
        {"glLoadTransposeMatrixf", pnames1455, '.', "."},
        {"glLoadTransposeMatrixfARB", pnames1456, '.', "."},
        {"glLoadTransposeMatrixxOES", pnames1457, '.', "."},
        {"glLockArraysEXT", pnames1458, '.', ".."},
        {"glLogicOp", pnames1459, '.', "E"},
        {"glMakeBufferNonResidentNV", pnames1460, '.', "E"},
        {"glMakeBufferResidentNV", pnames1461, '.', "EE"},
        {"glMakeImageHandleNonResidentARB", pnames1462, '.', "."},
        {"glMakeImageHandleNonResidentNV", pnames1463, '.', "."},
        {"glMakeImageHandleResidentARB", pnames1464, '.', ".E"},
        {"glMakeImageHandleResidentNV", pnames1465, '.', ".E"},
        {"glMakeNamedBufferNonResidentNV", pnames1466, '.', "."},
        {"glMakeNamedBufferResidentNV", pnames1467, '.', ".E"},
        {"glMakeTextureHandleNonResidentARB", pnames1468, '.', "."},
        {"glMakeTextureHandleNonResidentNV", pnames1469, '.', "."},
        {"glMakeTextureHandleResidentARB", pnames1470, '.', "."},
        {"glMakeTextureHandleResidentNV", pnames1471, '.', "."},
        {"glMap1d", pnames1472, '.', "E....."},
        {"glMap1f", pnames1473, '.', "E....."},
        {"glMap1xOES", pnames1474, '.', "E....."},
        {"glMap2d", pnames1475, '.', "E........."},
        {"glMap2f", pnames1476, '.', "E........."},
        {"glMap2xOES", pnames1477, '.', "E........."},
        {"glMapBuffer", pnames1478, '.', "EE"},
        {"glMapBufferARB", pnames1479, '.', "EE"},
        {"glMapBufferOES", pnames1480, '.', "EE"},
        {"glMapBufferRange", pnames1481, '.', "E..F"},
        {"glMapBufferRangeEXT", pnames1482, '.', "E..F"},
        {"glMapControlPointsNV", pnames1483, '.', "E.E....B."},
        {"glMapGrid1d", pnames1484, '.', "..."},
        {"glMapGrid1f", pnames1485, '.', "..."},
        {"glMapGrid1xOES", pnames1486, '.', "..."},
        {"glMapGrid2d", pnames1487, '.', "......"},
        {"glMapGrid2f", pnames1488, '.', "......"},
        {"glMapGrid2xOES", pnames1489, '.', "....."},
        {"glMapNamedBuffer", pnames1490, '.', ".E"},
        {"glMapNamedBufferEXT", pnames1491, '.', ".E"},
        {"glMapNamedBufferRange", pnames1492, '.', "...F"},
        {"glMapNamedBufferRangeEXT", pnames1493, '.', "...F"},
        {"glMapObjectBufferATI", pnames1494, '.', "."},
        {"glMapParameterfvNV", pnames1495, '.', "EE."},
        {"glMapParameterivNV", pnames1496, '.', "EE."},
        {"glMapTexture2DINTEL", pnames1497, '.', "..F.."},
        {"glMapVertexAttrib1dAPPLE", pnames1498, '.', "......."},
        {"glMapVertexAttrib1fAPPLE", pnames1499, '.', "......."},
        {"glMapVertexAttrib2dAPPLE", pnames1500, '.', "..........."},
        {"glMapVertexAttrib2fAPPLE", pnames1501, '.', "..........."},
        {"glMaterialf", pnames1502, '.', "EE."},
        {"glMaterialfv", pnames1503, '.', "EE."},
        {"glMateriali", pnames1504, '.', "EE."},
        {"glMaterialiv", pnames1505, '.', "EE."},
        {"glMaterialx", pnames1506, '.', "EE."},
        {"glMaterialxOES", pnames1507, '.', "EE."},
        {"glMaterialxv", pnames1508, '.', "EE."},
        {"glMaterialxvOES", pnames1509, '.', "EE."},
        {"glMatrixFrustumEXT", pnames1510, '.', "E......"},
        {"glMatrixIndexPointerARB", pnames1511, '.', ".E.."},
        {"glMatrixIndexPointerOES", pnames1512, '.', ".E.."},
        {"glMatrixIndexubvARB", pnames1513, '.', ".."},
        {"glMatrixIndexuivARB", pnames1514, '.', ".."},
        {"glMatrixIndexusvARB", pnames1515, '.', ".."},
        {"glMatrixLoad3x2fNV", pnames1516, '.', "E."},
        {"glMatrixLoad3x3fNV", pnames1517, '.', "E."},
        {"glMatrixLoadIdentityEXT", pnames1518, '.', "E"},
        {"glMatrixLoadTranspose3x3fNV", pnames1519, '.', "E."},
        {"glMatrixLoadTransposedEXT", pnames1520, '.', "E."},
        {"glMatrixLoadTransposefEXT", pnames1521, '.', "E."},
        {"glMatrixLoaddEXT", pnames1522, '.', "E."},
        {"glMatrixLoadfEXT", pnames1523, '.', "E."},
        {"glMatrixMode", pnames1524, '.', "E"},
        {"glMatrixMult3x2fNV", pnames1525, '.', "E."},
        {"glMatrixMult3x3fNV", pnames1526, '.', "E."},
        {"glMatrixMultTranspose3x3fNV", pnames1527, '.', "E."},
        {"glMatrixMultTransposedEXT", pnames1528, '.', "E."},
        {"glMatrixMultTransposefEXT", pnames1529, '.', "E."},
        {"glMatrixMultdEXT", pnames1530, '.', "E."},
        {"glMatrixMultfEXT", pnames1531, '.', "E."},
        {"glMatrixOrthoEXT", pnames1532, '.', "E......"},
        {"glMatrixPopEXT", pnames1533, '.', "E"},
        {"glMatrixPushEXT", pnames1534, '.', "E"},
        {"glMatrixRotatedEXT", pnames1535, '.', "E...."},
        {"glMatrixRotatefEXT", pnames1536, '.', "E...."},
        {"glMatrixScaledEXT", pnames1537, '.', "E..."},
        {"glMatrixScalefEXT", pnames1538, '.', "E..."},
        {"glMatrixTranslatedEXT", pnames1539, '.', "E..."},
        {"glMatrixTranslatefEXT", pnames1540, '.', "E..."},
        {"glMaxShaderCompilerThreadsARB", pnames1541, '.', "."},
        {"glMemoryBarrier", pnames1542, '.', "F"},
        {"glMemoryBarrierByRegion", pnames1543, '.', "F"},
        {"glMemoryBarrierEXT", pnames1544, '.', "F"},
        {"glMinSampleShading", pnames1545, '.', "."},
        {"glMinSampleShadingARB", pnames1546, '.', "."},
        {"glMinSampleShadingOES", pnames1547, '.', "."},
        {"glMinmax", pnames1548, '.', "EEB"},
        {"glMinmaxEXT", pnames1549, '.', "EEB"},
        {"glMultMatrixd", pnames1550, '.', "."},
        {"glMultMatrixf", pnames1551, '.', "."},
        {"glMultMatrixx", pnames1552, '.', "."},
        {"glMultMatrixxOES", pnames1553, '.', "."},
        {"glMultTransposeMatrixd", pnames1554, '.', "."},
        {"glMultTransposeMatrixdARB", pnames1555, '.', "."},
        {"glMultTransposeMatrixf", pnames1556, '.', "."},
        {"glMultTransposeMatrixfARB", pnames1557, '.', "."},
        {"glMultTransposeMatrixxOES", pnames1558, '.', "."},
        {"glMultiDrawArrays", pnames1559, '.', "E..."},
        {"glMultiDrawArraysEXT", pnames1560, '.', "E..."},
        {"glMultiDrawArraysIndirect", pnames1561, '.', "E..."},
        {"glMultiDrawArraysIndirectAMD", pnames1562, '.', "E..."},
        {"glMultiDrawArraysIndirectBindlessCountNV", pnames1563, '.', "E....."},
        {"glMultiDrawArraysIndirectBindlessNV", pnames1564, '.', "E...."},
        {"glMultiDrawArraysIndirectCountARB", pnames1565, '.', "E...."},
        {"glMultiDrawArraysIndirectEXT", pnames1566, '.', "E..."},
        {"glMultiDrawElementArrayAPPLE", pnames1567, '.', "E..."},
        {"glMultiDrawElements", pnames1568, '.', "E.E.."},
        {"glMultiDrawElementsBaseVertex", pnames1569, '.', "E.E..."},
        {"glMultiDrawElementsBaseVertexEXT", pnames1570, '.', "E.E..."},
        {"glMultiDrawElementsBaseVertexOES", pnames1571, '.', "E.E..."},
        {"glMultiDrawElementsEXT", pnames1572, '.', "E.E.."},
        {"glMultiDrawElementsIndirect", pnames1573, '.', "EE..."},
        {"glMultiDrawElementsIndirectAMD", pnames1574, '.', "EE..."},
        {"glMultiDrawElementsIndirectBindlessCountNV", pnames1575, '.', "EE....."},
        {"glMultiDrawElementsIndirectBindlessNV", pnames1576, '.', "EE...."},
        {"glMultiDrawElementsIndirectCountARB", pnames1577, '.', "EE...."},
        {"glMultiDrawElementsIndirectEXT", pnames1578, '.', "EE..."},
        {"glMultiDrawRangeElementArrayAPPLE", pnames1579, '.', "E....."},
        {"glMultiModeDrawArraysIBM", pnames1580, '.', "....."},
        {"glMultiModeDrawElementsIBM", pnames1581, '.', "..E..."},
        {"glMultiTexBufferEXT", pnames1582, '.', "EEE."},
        {"glMultiTexCoord1bOES", pnames1583, '.', "E."},
        {"glMultiTexCoord1bvOES", pnames1584, '.', "E."},
        {"glMultiTexCoord1d", pnames1585, '.', "E."},
        {"glMultiTexCoord1dARB", pnames1586, '.', "E."},
        {"glMultiTexCoord1dv", pnames1587, '.', "E."},
        {"glMultiTexCoord1dvARB", pnames1588, '.', "E."},
        {"glMultiTexCoord1f", pnames1589, '.', "E."},
        {"glMultiTexCoord1fARB", pnames1590, '.', "E."},
        {"glMultiTexCoord1fv", pnames1591, '.', "E."},
        {"glMultiTexCoord1fvARB", pnames1592, '.', "E."},
        {"glMultiTexCoord1hNV", pnames1593, '.', "E."},
        {"glMultiTexCoord1hvNV", pnames1594, '.', "E."},
        {"glMultiTexCoord1i", pnames1595, '.', "E."},
        {"glMultiTexCoord1iARB", pnames1596, '.', "E."},
        {"glMultiTexCoord1iv", pnames1597, '.', "E."},
        {"glMultiTexCoord1ivARB", pnames1598, '.', "E."},
        {"glMultiTexCoord1s", pnames1599, '.', "E."},
        {"glMultiTexCoord1sARB", pnames1600, '.', "E."},
        {"glMultiTexCoord1sv", pnames1601, '.', "E."},
        {"glMultiTexCoord1svARB", pnames1602, '.', "E."},
        {"glMultiTexCoord1xOES", pnames1603, '.', "E."},
        {"glMultiTexCoord1xvOES", pnames1604, '.', "E."},
        {"glMultiTexCoord2bOES", pnames1605, '.', "E.."},
        {"glMultiTexCoord2bvOES", pnames1606, '.', "E."},
        {"glMultiTexCoord2d", pnames1607, '.', "E.."},
        {"glMultiTexCoord2dARB", pnames1608, '.', "E.."},
        {"glMultiTexCoord2dv", pnames1609, '.', "E."},
        {"glMultiTexCoord2dvARB", pnames1610, '.', "E."},
        {"glMultiTexCoord2f", pnames1611, '.', "E.."},
        {"glMultiTexCoord2fARB", pnames1612, '.', "E.."},
        {"glMultiTexCoord2fv", pnames1613, '.', "E."},
        {"glMultiTexCoord2fvARB", pnames1614, '.', "E."},
        {"glMultiTexCoord2hNV", pnames1615, '.', "E.."},
        {"glMultiTexCoord2hvNV", pnames1616, '.', "E."},
        {"glMultiTexCoord2i", pnames1617, '.', "E.."},
        {"glMultiTexCoord2iARB", pnames1618, '.', "E.."},
        {"glMultiTexCoord2iv", pnames1619, '.', "E."},
        {"glMultiTexCoord2ivARB", pnames1620, '.', "E."},
        {"glMultiTexCoord2s", pnames1621, '.', "E.."},
        {"glMultiTexCoord2sARB", pnames1622, '.', "E.."},
        {"glMultiTexCoord2sv", pnames1623, '.', "E."},
        {"glMultiTexCoord2svARB", pnames1624, '.', "E."},
        {"glMultiTexCoord2xOES", pnames1625, '.', "E.."},
        {"glMultiTexCoord2xvOES", pnames1626, '.', "E."},
        {"glMultiTexCoord3bOES", pnames1627, '.', "E..."},
        {"glMultiTexCoord3bvOES", pnames1628, '.', "E."},
        {"glMultiTexCoord3d", pnames1629, '.', "E..."},
        {"glMultiTexCoord3dARB", pnames1630, '.', "E..."},
        {"glMultiTexCoord3dv", pnames1631, '.', "E."},
        {"glMultiTexCoord3dvARB", pnames1632, '.', "E."},
        {"glMultiTexCoord3f", pnames1633, '.', "E..."},
        {"glMultiTexCoord3fARB", pnames1634, '.', "E..."},
        {"glMultiTexCoord3fv", pnames1635, '.', "E."},
        {"glMultiTexCoord3fvARB", pnames1636, '.', "E."},
        {"glMultiTexCoord3hNV", pnames1637, '.', "E..."},
        {"glMultiTexCoord3hvNV", pnames1638, '.', "E."},
        {"glMultiTexCoord3i", pnames1639, '.', "E..."},
        {"glMultiTexCoord3iARB", pnames1640, '.', "E..."},
        {"glMultiTexCoord3iv", pnames1641, '.', "E."},
        {"glMultiTexCoord3ivARB", pnames1642, '.', "E."},
        {"glMultiTexCoord3s", pnames1643, '.', "E..."},
        {"glMultiTexCoord3sARB", pnames1644, '.', "E..."},
        {"glMultiTexCoord3sv", pnames1645, '.', "E."},
        {"glMultiTexCoord3svARB", pnames1646, '.', "E."},
        {"glMultiTexCoord3xOES", pnames1647, '.', "E..."},
        {"glMultiTexCoord3xvOES", pnames1648, '.', "E."},
        {"glMultiTexCoord4bOES", pnames1649, '.', "E...."},
        {"glMultiTexCoord4bvOES", pnames1650, '.', "E."},
        {"glMultiTexCoord4d", pnames1651, '.', "E...."},
        {"glMultiTexCoord4dARB", pnames1652, '.', "E...."},
        {"glMultiTexCoord4dv", pnames1653, '.', "E."},
        {"glMultiTexCoord4dvARB", pnames1654, '.', "E."},
        {"glMultiTexCoord4f", pnames1655, '.', "E...."},
        {"glMultiTexCoord4fARB", pnames1656, '.', "E...."},
        {"glMultiTexCoord4fv", pnames1657, '.', "E."},
        {"glMultiTexCoord4fvARB", pnames1658, '.', "E."},
        {"glMultiTexCoord4hNV", pnames1659, '.', "E...."},
        {"glMultiTexCoord4hvNV", pnames1660, '.', "E."},
        {"glMultiTexCoord4i", pnames1661, '.', "E...."},
        {"glMultiTexCoord4iARB", pnames1662, '.', "E...."},
        {"glMultiTexCoord4iv", pnames1663, '.', "E."},
        {"glMultiTexCoord4ivARB", pnames1664, '.', "E."},
        {"glMultiTexCoord4s", pnames1665, '.', "E...."},
        {"glMultiTexCoord4sARB", pnames1666, '.', "E...."},
        {"glMultiTexCoord4sv", pnames1667, '.', "E."},
        {"glMultiTexCoord4svARB", pnames1668, '.', "E."},
        {"glMultiTexCoord4x", pnames1669, '.', "E...."},
        {"glMultiTexCoord4xOES", pnames1670, '.', "E...."},
        {"glMultiTexCoord4xvOES", pnames1671, '.', "E."},
        {"glMultiTexCoordP1ui", pnames1672, '.', "EE."},
        {"glMultiTexCoordP1uiv", pnames1673, '.', "EE."},
        {"glMultiTexCoordP2ui", pnames1674, '.', "EE."},
        {"glMultiTexCoordP2uiv", pnames1675, '.', "EE."},
        {"glMultiTexCoordP3ui", pnames1676, '.', "EE."},
        {"glMultiTexCoordP3uiv", pnames1677, '.', "EE."},
        {"glMultiTexCoordP4ui", pnames1678, '.', "EE."},
        {"glMultiTexCoordP4uiv", pnames1679, '.', "EE."},
        {"glMultiTexCoordPointerEXT", pnames1680, '.', "E.E.."},
        {"glMultiTexEnvfEXT", pnames1681, '.', "EEE."},
        {"glMultiTexEnvfvEXT", pnames1682, '.', "EEE."},
        {"glMultiTexEnviEXT", pnames1683, '.', "EEE."},
        {"glMultiTexEnvivEXT", pnames1684, '.', "EEE."},
        {"glMultiTexGendEXT", pnames1685, '.', "EEE."},
        {"glMultiTexGendvEXT", pnames1686, '.', "EEE."},
        {"glMultiTexGenfEXT", pnames1687, '.', "EEE."},
        {"glMultiTexGenfvEXT", pnames1688, '.', "EEE."},
        {"glMultiTexGeniEXT", pnames1689, '.', "EEE."},
        {"glMultiTexGenivEXT", pnames1690, '.', "EEE."},
        {"glMultiTexImage1DEXT", pnames1691, '.', "EE....EE."},
        {"glMultiTexImage2DEXT", pnames1692, '.', "EE.....EE."},
        {"glMultiTexImage3DEXT", pnames1693, '.', "EE......EE."},
        {"glMultiTexParameterIivEXT", pnames1694, '.', "EEE."},
        {"glMultiTexParameterIuivEXT", pnames1695, '.', "EEE."},
        {"glMultiTexParameterfEXT", pnames1696, '.', "EEE."},
        {"glMultiTexParameterfvEXT", pnames1697, '.', "EEE."},
        {"glMultiTexParameteriEXT", pnames1698, '.', "EEE."},
        {"glMultiTexParameterivEXT", pnames1699, '.', "EEE."},
        {"glMultiTexRenderbufferEXT", pnames1700, '.', "EE."},
        {"glMultiTexSubImage1DEXT", pnames1701, '.', "EE...EE."},
        {"glMultiTexSubImage2DEXT", pnames1702, '.', "EE.....EE."},
        {"glMultiTexSubImage3DEXT", pnames1703, '.', "EE.......EE."},
        {"glNamedBufferData", pnames1704, '.', "...E"},
        {"glNamedBufferDataEXT", pnames1705, '.', "...E"},
        {"glNamedBufferPageCommitmentARB", pnames1706, '.', "...B"},
        {"glNamedBufferPageCommitmentEXT", pnames1707, '.', "...B"},
        {"glNamedBufferStorage", pnames1708, '.', "...F"},
        {"glNamedBufferStorageEXT", pnames1709, '.', "...F"},
        {"glNamedBufferSubData", pnames1710, '.', "...."},
        {"glNamedBufferSubDataEXT", pnames1711, '.', "...."},
        {"glNamedCopyBufferSubDataEXT", pnames1712, '.', "....."},
        {"glNamedFramebufferDrawBuffer", pnames1713, '.', ".E"},
        {"glNamedFramebufferDrawBuffers", pnames1714, '.', "..."},
        {"glNamedFramebufferParameteri", pnames1715, '.', ".E."},
        {"glNamedFramebufferParameteriEXT", pnames1716, '.', ".E."},
        {"glNamedFramebufferReadBuffer", pnames1717, '.', ".E"},
        {"glNamedFramebufferRenderbuffer", pnames1718, '.', ".EE."},
        {"glNamedFramebufferRenderbufferEXT", pnames1719, '.', ".EE."},
        {"glNamedFramebufferSampleLocationsfvARB", pnames1720, '.', "...."},
        {"glNamedFramebufferSampleLocationsfvNV", pnames1721, '.', "...."},
        {"glNamedFramebufferTexture", pnames1722, '.', ".E.."},
        {"glNamedFramebufferSamplePositionsfvAMD", pnames1723, '.', "...."},
        {"glNamedFramebufferTexture1DEXT", pnames1724, '.', ".EE.."},
        {"glNamedFramebufferTexture2DEXT", pnames1725, '.', ".EE.."},
        {"glNamedFramebufferTexture3DEXT", pnames1726, '.', ".EE..."},
        {"glNamedFramebufferTextureEXT", pnames1727, '.', ".E.."},
        {"glNamedFramebufferTextureFaceEXT", pnames1728, '.', ".E..E"},
        {"glNamedFramebufferTextureLayer", pnames1729, '.', ".E..."},
        {"glNamedFramebufferTextureLayerEXT", pnames1730, '.', ".E..."},
        {"glNamedProgramLocalParameter4dEXT", pnames1731, '.', ".E....."},
        {"glNamedProgramLocalParameter4dvEXT", pnames1732, '.', ".E.."},
        {"glNamedProgramLocalParameter4fEXT", pnames1733, '.', ".E....."},
        {"glNamedProgramLocalParameter4fvEXT", pnames1734, '.', ".E.."},
        {"glNamedProgramLocalParameterI4iEXT", pnames1735, '.', ".E....."},
        {"glNamedProgramLocalParameterI4ivEXT", pnames1736, '.', ".E.."},
        {"glNamedProgramLocalParameterI4uiEXT", pnames1737, '.', ".E....."},
        {"glNamedProgramLocalParameterI4uivEXT", pnames1738, '.', ".E.."},
        {"glNamedProgramLocalParameters4fvEXT", pnames1739, '.', ".E..."},
        {"glNamedProgramLocalParametersI4ivEXT", pnames1740, '.', ".E..."},
        {"glNamedProgramLocalParametersI4uivEXT", pnames1741, '.', ".E..."},
        {"glNamedProgramStringEXT", pnames1742, '.', ".EE.."},
        {"glNamedRenderbufferStorage", pnames1743, '.', ".E.."},
        {"glNamedRenderbufferStorageEXT", pnames1744, '.', ".E.."},
        {"glNamedRenderbufferStorageMultisample", pnames1745, '.', "..E.."},
        {"glNamedRenderbufferStorageMultisampleCoverageEXT", pnames1746, '.', "...E.."},
        {"glNamedRenderbufferStorageMultisampleEXT", pnames1747, '.', "..E.."},
        {"glNamedStringARB", pnames1748, '.', "E...."},
        {"glNewList", pnames1749, '.', ".E"},
        {"glNewObjectBufferATI", pnames1750, '.', "..E"},
        {"glNormal3b", pnames1751, '.', "..."},
        {"glNormal3bv", pnames1752, '.', "."},
        {"glNormal3d", pnames1753, '.', "..."},
        {"glNormal3dv", pnames1754, '.', "."},
        {"glNormal3f", pnames1755, '.', "..."},
        {"glNormal3fVertex3fSUN", pnames1756, '.', "......"},
        {"glNormal3fVertex3fvSUN", pnames1757, '.', ".."},
        {"glNormal3fv", pnames1758, '.', "."},
        {"glNormal3hNV", pnames1759, '.', "..."},
        {"glNormal3hvNV", pnames1760, '.', "."},
        {"glNormal3i", pnames1761, '.', "..."},
        {"glNormal3iv", pnames1762, '.', "."},
        {"glNormal3s", pnames1763, '.', "..."},
        {"glNormal3sv", pnames1764, '.', "."},
        {"glNormal3x", pnames1765, '.', "..."},
        {"glNormal3xOES", pnames1766, '.', "..."},
        {"glNormal3xvOES", pnames1767, '.', "."},
        {"glNormalFormatNV", pnames1768, '.', "E."},
        {"glNormalP3ui", pnames1769, '.', "E."},
        {"glNormalP3uiv", pnames1770, '.', "E."},
        {"glNormalPointer", pnames1771, '.', "E.."},
        {"glNormalPointerEXT", pnames1772, '.', "E..."},
        {"glNormalPointerListIBM", pnames1773, '.', "E..."},
        {"glNormalPointervINTEL", pnames1774, '.', "E."},
        {"glNormalStream3bATI", pnames1775, '.', "E..."},
        {"glNormalStream3bvATI", pnames1776, '.', "E."},
        {"glNormalStream3dATI", pnames1777, '.', "E..."},
        {"glNormalStream3dvATI", pnames1778, '.', "E."},
        {"glNormalStream3fATI", pnames1779, '.', "E..."},
        {"glNormalStream3fvATI", pnames1780, '.', "E."},
        {"glNormalStream3iATI", pnames1781, '.', "E..."},
        {"glNormalStream3ivATI", pnames1782, '.', "E."},
        {"glNormalStream3sATI", pnames1783, '.', "E..."},
        {"glNormalStream3svATI", pnames1784, '.', "E."},
        {"glObjectLabel", pnames1785, '.', "E..."},
        {"glObjectLabelKHR", pnames1786, '.', "E..."},
        {"glObjectPtrLabel", pnames1787, '.', "..."},
        {"glObjectPtrLabelKHR", pnames1788, '.', "..."},
        {"glObjectPurgeableAPPLE", pnames1789, 'E', "E.E"},
        {"glObjectUnpurgeableAPPLE", pnames1790, 'E', "E.E"},
        {"glOrtho", pnames1791, '.', "......"},
        {"glOrthof", pnames1792, '.', "......"},
        {"glOrthofOES", pnames1793, '.', "......"},
        {"glOrthox", pnames1794, '.', "......"},
        {"glOrthoxOES", pnames1795, '.', "......"},
        {"glPNTrianglesfATI", pnames1796, '.', "E."},
        {"glPNTrianglesiATI", pnames1797, '.', "E."},
        {"glPassTexCoordATI", pnames1798, '.', "..E"},
        {"glPassThrough", pnames1799, '.', "."},
        {"glPassThroughxOES", pnames1800, '.', "."},
        {"glPatchParameterfv", pnames1801, '.', "E."},
        {"glPatchParameteri", pnames1802, '.', "E."},
        {"glPatchParameteriEXT", pnames1803, '.', "E."},
        {"glPatchParameteriOES", pnames1804, '.', "E."},
        {"glPathColorGenNV", pnames1805, '.', "EEE."},
        {"glPathCommandsNV", pnames1806, '.', "....E."},
        {"glPathCoordsNV", pnames1807, '.', "..E."},
        {"glPathCoverDepthFuncNV", pnames1808, '.', "E"},
        {"glPathDashArrayNV", pnames1809, '.', "..."},
        {"glPathFogGenNV", pnames1810, '.', "E"},
        {"glPathGlyphIndexArrayNV", pnames1811, 'E', ".E.F...."},
        {"glPathGlyphIndexRangeNV", pnames1812, 'E', "E.F..."},
        {"glPathGlyphRangeNV", pnames1813, '.', ".E.F..E.."},
        {"glPathGlyphsNV", pnames1814, '.', ".E.F.E.E.."},
        {"glPathMemoryGlyphIndexArrayNV", pnames1815, 'E', ".E......."},
        {"glPathParameterfNV", pnames1816, '.', ".E."},
        {"glPathParameterfvNV", pnames1817, '.', ".E."},
        {"glPathParameteriNV", pnames1818, '.', ".E."},
        {"glPathParameterivNV", pnames1819, '.', ".E."},
        {"glPathStencilDepthOffsetNV", pnames1820, '.', ".."},
        {"glPathStencilFuncNV", pnames1821, '.', "E.."},
        {"glPathStringNV", pnames1822, '.', ".E.."},
        {"glPathSubCommandsNV", pnames1823, '.', "......E."},
        {"glPathSubCoordsNV", pnames1824, '.', "...E."},
        {"glPathTexGenNV", pnames1825, '.', "EE.."},
        {"glPauseTransformFeedback", pnames1826, '.', ""},
        {"glPauseTransformFeedbackNV", pnames1827, '.', ""},
        {"glPixelDataRangeNV", pnames1828, '.', "E.."},
        {"glPixelMapfv", pnames1829, '.', "E.."},
        {"glPixelMapuiv", pnames1830, '.', "E.."},
        {"glPixelMapusv", pnames1831, '.', "E.."},
        {"glPixelMapx", pnames1832, '.', "E.."},
        {"glPixelStoref", pnames1833, '.', "E."},
        {"glPixelStorei", pnames1834, '.', "E."},
        {"glPixelStorex", pnames1835, '.', "E."},
        {"glPixelTexGenParameterfSGIS", pnames1836, '.', "E."},
        {"glPixelTexGenParameterfvSGIS", pnames1837, '.', "E."},
        {"glPixelTexGenParameteriSGIS", pnames1838, '.', "E."},
        {"glPixelTexGenParameterivSGIS", pnames1839, '.', "E."},
        {"glPixelTexGenSGIX", pnames1840, '.', "E"},
        {"glPixelTransferf", pnames1841, '.', "E."},
        {"glPixelTransferi", pnames1842, '.', "E."},
        {"glPixelTransferxOES", pnames1843, '.', "E."},
        {"glPixelTransformParameterfEXT", pnames1844, '.', "EE."},
        {"glPixelTransformParameterfvEXT", pnames1845, '.', "EE."},
        {"glPixelTransformParameteriEXT", pnames1846, '.', "EE."},
        {"glPixelTransformParameterivEXT", pnames1847, '.', "EE."},
        {"glPixelZoom", pnames1848, '.', ".."},
        {"glPixelZoomxOES", pnames1849, '.', ".."},
        {"glPointAlongPathNV", pnames1850, 'B', "........"},
        {"glPointParameterf", pnames1851, '.', "E."},
        {"glPointParameterfARB", pnames1852, '.', "E."},
        {"glPointParameterfEXT", pnames1853, '.', "E."},
        {"glPointParameterfSGIS", pnames1854, '.', "E."},
        {"glPointParameterfv", pnames1855, '.', "E."},
        {"glPointParameterfvARB", pnames1856, '.', "E."},
        {"glPointParameterfvEXT", pnames1857, '.', "E."},
        {"glPointParameterfvSGIS", pnames1858, '.', "E."},
        {"glPointParameteri", pnames1859, '.', "E."},
        {"glPointParameteriNV", pnames1860, '.', "E."},
        {"glPointParameteriv", pnames1861, '.', "E."},
        {"glPointParameterivNV", pnames1862, '.', "E."},
        {"glPointParameterx", pnames1863, '.', "E."},
        {"glPointParameterxOES", pnames1864, '.', "E."},
        {"glPointParameterxv", pnames1865, '.', "E."},
        {"glPointParameterxvOES", pnames1866, '.', "E."},
        {"glPointSize", pnames1867, '.', "."},
        {"glPointSizePointerOES", pnames1868, '.', "E.."},
        {"glPointSizex", pnames1869, '.', "."},
        {"glPointSizexOES", pnames1870, '.', "."},
        {"glPollAsyncSGIX", pnames1871, '.', "."},
        {"glPollInstrumentsSGIX", pnames1872, '.', "."},
        {"glPolygonMode", pnames1873, '.', "EE"},
        {"glPolygonModeNV", pnames1874, '.', "EE"},
        {"glPolygonOffset", pnames1875, '.', ".."},
        {"glPolygonOffsetClampEXT", pnames1876, '.', "..."},
        {"glPolygonOffsetEXT", pnames1877, '.', ".."},
        {"glPolygonOffsetx", pnames1878, '.', ".."},
        {"glPolygonOffsetxOES", pnames1879, '.', ".."},
        {"glPolygonStipple", pnames1880, '.', "."},
        {"glPopAttrib", pnames1881, '.', ""},
        {"glPopClientAttrib", pnames1882, '.', ""},
        {"glPopDebugGroup", pnames1883, '.', ""},
        {"glPopDebugGroupKHR", pnames1884, '.', ""},
        {"glPopGroupMarkerEXT", pnames1885, '.', ""},
        {"glPopMatrix", pnames1886, '.', ""},
        {"glPopName", pnames1887, '.', ""},
        {"glPresentFrameDualFillNV", pnames1888, '.', "....EE.E.E.E."},
        {"glPresentFrameKeyedNV", pnames1889, '.', "....EE..E.."},
        {"glPrimitiveBoundingBox", pnames1890, '.', "........"},
        {"glPrimitiveBoundingBoxARB", pnames1891, '.', "........"},
        {"glPrimitiveBoundingBoxEXT", pnames1892, '.', "........"},
        {"glPrimitiveBoundingBoxOES", pnames1893, '.', "........"},
        {"glPrimitiveRestartIndex", pnames1894, '.', "."},
        {"glPrimitiveRestartIndexNV", pnames1895, '.', "."},
        {"glPrimitiveRestartNV", pnames1896, '.', ""},
        {"glPrioritizeTextures", pnames1897, '.', "..."},
        {"glPrioritizeTexturesEXT", pnames1898, '.', "..."},
        {"glPrioritizeTexturesxOES", pnames1899, '.', "..."},
        {"glProgramBinary", pnames1900, '.', ".E.."},
        {"glProgramBinaryOES", pnames1901, '.', ".E.."},
        {"glProgramBufferParametersIivNV", pnames1902, '.', "E...."},
        {"glProgramBufferParametersIuivNV", pnames1903, '.', "E...."},
        {"glProgramBufferParametersfvNV", pnames1904, '.', "E...."},
        {"glProgramEnvParameter4dARB", pnames1905, '.', "E....."},
        {"glProgramEnvParameter4dvARB", pnames1906, '.', "E.."},
        {"glProgramEnvParameter4fARB", pnames1907, '.', "E....."},
        {"glProgramEnvParameter4fvARB", pnames1908, '.', "E.."},
        {"glProgramEnvParameterI4iNV", pnames1909, '.', "E....."},
        {"glProgramEnvParameterI4ivNV", pnames1910, '.', "E.."},
        {"glProgramEnvParameterI4uiNV", pnames1911, '.', "E....."},
        {"glProgramEnvParameterI4uivNV", pnames1912, '.', "E.."},
        {"glProgramEnvParameters4fvEXT", pnames1913, '.', "E..."},
        {"glProgramEnvParametersI4ivNV", pnames1914, '.', "E..."},
        {"glProgramEnvParametersI4uivNV", pnames1915, '.', "E..."},
        {"glProgramLocalParameter4dARB", pnames1916, '.', "E....."},
        {"glProgramLocalParameter4dvARB", pnames1917, '.', "E.."},
        {"glProgramLocalParameter4fARB", pnames1918, '.', "E....."},
        {"glProgramLocalParameter4fvARB", pnames1919, '.', "E.."},
        {"glProgramLocalParameterI4iNV", pnames1920, '.', "E....."},
        {"glProgramLocalParameterI4ivNV", pnames1921, '.', "E.."},
        {"glProgramLocalParameterI4uiNV", pnames1922, '.', "E....."},
        {"glProgramLocalParameterI4uivNV", pnames1923, '.', "E.."},
        {"glProgramLocalParameters4fvEXT", pnames1924, '.', "E..."},
        {"glProgramLocalParametersI4ivNV", pnames1925, '.', "E..."},
        {"glProgramLocalParametersI4uivNV", pnames1926, '.', "E..."},
        {"glProgramNamedParameter4dNV", pnames1927, '.', "......."},
        {"glProgramNamedParameter4dvNV", pnames1928, '.', "...."},
        {"glProgramNamedParameter4fNV", pnames1929, '.', "......."},
        {"glProgramNamedParameter4fvNV", pnames1930, '.', "...."},
        {"glProgramParameter4dNV", pnames1931, '.', "E....."},
        {"glProgramParameter4dvNV", pnames1932, '.', "E.."},
        {"glProgramParameter4fNV", pnames1933, '.', "E....."},
        {"glProgramParameter4fvNV", pnames1934, '.', "E.."},
        {"glProgramParameteri", pnames1935, '.', ".E."},
        {"glProgramParameteriARB", pnames1936, '.', ".E."},
        {"glProgramParameteriEXT", pnames1937, '.', ".E."},
        {"glProgramParameters4dvNV", pnames1938, '.', "E..."},
        {"glProgramParameters4fvNV", pnames1939, '.', "E..."},
        {"glProgramPathFragmentInputGenNV", pnames1940, '.', "..E.."},
        {"glProgramStringARB", pnames1941, '.', "EE.."},
        {"glProgramSubroutineParametersuivNV", pnames1942, '.', "E.."},
        {"glProgramUniform1d", pnames1943, '.', "..."},
        {"glProgramUniform1dEXT", pnames1944, '.', "..."},
        {"glProgramUniform1dv", pnames1945, '.', "...."},
        {"glProgramUniform1dvEXT", pnames1946, '.', "...."},
        {"glProgramUniform1f", pnames1947, '.', "..."},
        {"glProgramUniform1fEXT", pnames1948, '.', "..."},
        {"glProgramUniform1fv", pnames1949, '.', "...."},
        {"glProgramUniform1fvEXT", pnames1950, '.', "...."},
        {"glProgramUniform1i", pnames1951, '.', "..."},
        {"glProgramUniform1i64ARB", pnames1952, '.', "..."},
        {"glProgramUniform1i64NV", pnames1953, '.', "..."},
        {"glProgramUniform1i64vARB", pnames1954, '.', "...."},
        {"glProgramUniform1i64vNV", pnames1955, '.', "...."},
        {"glProgramUniform1iEXT", pnames1956, '.', "..."},
        {"glProgramUniform1iv", pnames1957, '.', "...."},
        {"glProgramUniform1ivEXT", pnames1958, '.', "...."},
        {"glProgramUniform1ui", pnames1959, '.', "..."},
        {"glProgramUniform1ui64ARB", pnames1960, '.', "..."},
        {"glProgramUniform1ui64NV", pnames1961, '.', "..."},
        {"glProgramUniform1ui64vARB", pnames1962, '.', "...."},
        {"glProgramUniform1ui64vNV", pnames1963, '.', "...."},
        {"glProgramUniform1uiEXT", pnames1964, '.', "..."},
        {"glProgramUniform1uiv", pnames1965, '.', "...."},
        {"glProgramUniform1uivEXT", pnames1966, '.', "...."},
        {"glProgramUniform2d", pnames1967, '.', "...."},
        {"glProgramUniform2dEXT", pnames1968, '.', "...."},
        {"glProgramUniform2dv", pnames1969, '.', "...."},
        {"glProgramUniform2dvEXT", pnames1970, '.', "...."},
        {"glProgramUniform2f", pnames1971, '.', "...."},
        {"glProgramUniform2fEXT", pnames1972, '.', "...."},
        {"glProgramUniform2fv", pnames1973, '.', "...."},
        {"glProgramUniform2fvEXT", pnames1974, '.', "...."},
        {"glProgramUniform2i", pnames1975, '.', "...."},
        {"glProgramUniform2i64ARB", pnames1976, '.', "...."},
        {"glProgramUniform2i64NV", pnames1977, '.', "...."},
        {"glProgramUniform2i64vARB", pnames1978, '.', "...."},
        {"glProgramUniform2i64vNV", pnames1979, '.', "...."},
        {"glProgramUniform2iEXT", pnames1980, '.', "...."},
        {"glProgramUniform2iv", pnames1981, '.', "...."},
        {"glProgramUniform2ivEXT", pnames1982, '.', "...."},
        {"glProgramUniform2ui", pnames1983, '.', "...."},
        {"glProgramUniform2ui64ARB", pnames1984, '.', "...."},
        {"glProgramUniform2ui64NV", pnames1985, '.', "...."},
        {"glProgramUniform2ui64vARB", pnames1986, '.', "...."},
        {"glProgramUniform2ui64vNV", pnames1987, '.', "...."},
        {"glProgramUniform2uiEXT", pnames1988, '.', "...."},
        {"glProgramUniform2uiv", pnames1989, '.', "...."},
        {"glProgramUniform2uivEXT", pnames1990, '.', "...."},
        {"glProgramUniform3d", pnames1991, '.', "....."},
        {"glProgramUniform3dEXT", pnames1992, '.', "....."},
        {"glProgramUniform3dv", pnames1993, '.', "...."},
        {"glProgramUniform3dvEXT", pnames1994, '.', "...."},
        {"glProgramUniform3f", pnames1995, '.', "....."},
        {"glProgramUniform3fEXT", pnames1996, '.', "....."},
        {"glProgramUniform3fv", pnames1997, '.', "...."},
        {"glProgramUniform3fvEXT", pnames1998, '.', "...."},
        {"glProgramUniform3i", pnames1999, '.', "....."},
        {"glProgramUniform3i64ARB", pnames2000, '.', "....."},
        {"glProgramUniform3i64NV", pnames2001, '.', "....."},
        {"glProgramUniform3i64vARB", pnames2002, '.', "...."},
        {"glProgramUniform3i64vNV", pnames2003, '.', "...."},
        {"glProgramUniform3iEXT", pnames2004, '.', "....."},
        {"glProgramUniform3iv", pnames2005, '.', "...."},
        {"glProgramUniform3ivEXT", pnames2006, '.', "...."},
        {"glProgramUniform3ui", pnames2007, '.', "....."},
        {"glProgramUniform3ui64ARB", pnames2008, '.', "....."},
        {"glProgramUniform3ui64NV", pnames2009, '.', "....."},
        {"glProgramUniform3ui64vARB", pnames2010, '.', "...."},
        {"glProgramUniform3ui64vNV", pnames2011, '.', "...."},
        {"glProgramUniform3uiEXT", pnames2012, '.', "....."},
        {"glProgramUniform3uiv", pnames2013, '.', "...."},
        {"glProgramUniform3uivEXT", pnames2014, '.', "...."},
        {"glProgramUniform4d", pnames2015, '.', "......"},
        {"glProgramUniform4dEXT", pnames2016, '.', "......"},
        {"glProgramUniform4dv", pnames2017, '.', "...."},
        {"glProgramUniform4dvEXT", pnames2018, '.', "...."},
        {"glProgramUniform4f", pnames2019, '.', "......"},
        {"glProgramUniform4fEXT", pnames2020, '.', "......"},
        {"glProgramUniform4fv", pnames2021, '.', "...."},
        {"glProgramUniform4fvEXT", pnames2022, '.', "...."},
        {"glProgramUniform4i", pnames2023, '.', "......"},
        {"glProgramUniform4i64ARB", pnames2024, '.', "......"},
        {"glProgramUniform4i64NV", pnames2025, '.', "......"},
        {"glProgramUniform4i64vARB", pnames2026, '.', "...."},
        {"glProgramUniform4i64vNV", pnames2027, '.', "...."},
        {"glProgramUniform4iEXT", pnames2028, '.', "......"},
        {"glProgramUniform4iv", pnames2029, '.', "...."},
        {"glProgramUniform4ivEXT", pnames2030, '.', "...."},
        {"glProgramUniform4ui", pnames2031, '.', "......"},
        {"glProgramUniform4ui64ARB", pnames2032, '.', "......"},
        {"glProgramUniform4ui64NV", pnames2033, '.', "......"},
        {"glProgramUniform4ui64vARB", pnames2034, '.', "...."},
        {"glProgramUniform4ui64vNV", pnames2035, '.', "...."},
        {"glProgramUniform4uiEXT", pnames2036, '.', "......"},
        {"glProgramUniform4uiv", pnames2037, '.', "...."},
        {"glProgramUniform4uivEXT", pnames2038, '.', "...."},
        {"glProgramUniformHandleui64ARB", pnames2039, '.', "..."},
        {"glProgramUniformHandleui64IMG", pnames2040, '.', "..."},
        {"glProgramUniformHandleui64NV", pnames2041, '.', "..."},
        {"glProgramUniformHandleui64vARB", pnames2042, '.', "...."},
        {"glProgramUniformHandleui64vIMG", pnames2043, '.', "...."},
        {"glProgramUniformHandleui64vNV", pnames2044, '.', "...."},
        {"glProgramUniformMatrix2dv", pnames2045, '.', "...B."},
        {"glProgramUniformMatrix2dvEXT", pnames2046, '.', "...B."},
        {"glProgramUniformMatrix2fv", pnames2047, '.', "...B."},
        {"glProgramUniformMatrix2fvEXT", pnames2048, '.', "...B."},
        {"glProgramUniformMatrix2x3dv", pnames2049, '.', "...B."},
        {"glProgramUniformMatrix2x3dvEXT", pnames2050, '.', "...B."},
        {"glProgramUniformMatrix2x3fv", pnames2051, '.', "...B."},
        {"glProgramUniformMatrix2x3fvEXT", pnames2052, '.', "...B."},
        {"glProgramUniformMatrix2x4dv", pnames2053, '.', "...B."},
        {"glProgramUniformMatrix2x4dvEXT", pnames2054, '.', "...B."},
        {"glProgramUniformMatrix2x4fv", pnames2055, '.', "...B."},
        {"glProgramUniformMatrix2x4fvEXT", pnames2056, '.', "...B."},
        {"glProgramUniformMatrix3dv", pnames2057, '.', "...B."},
        {"glProgramUniformMatrix3dvEXT", pnames2058, '.', "...B."},
        {"glProgramUniformMatrix3fv", pnames2059, '.', "...B."},
        {"glProgramUniformMatrix3fvEXT", pnames2060, '.', "...B."},
        {"glProgramUniformMatrix3x2dv", pnames2061, '.', "...B."},
        {"glProgramUniformMatrix3x2dvEXT", pnames2062, '.', "...B."},
        {"glProgramUniformMatrix3x2fv", pnames2063, '.', "...B."},
        {"glProgramUniformMatrix3x2fvEXT", pnames2064, '.', "...B."},
        {"glProgramUniformMatrix3x4dv", pnames2065, '.', "...B."},
        {"glProgramUniformMatrix3x4dvEXT", pnames2066, '.', "...B."},
        {"glProgramUniformMatrix3x4fv", pnames2067, '.', "...B."},
        {"glProgramUniformMatrix3x4fvEXT", pnames2068, '.', "...B."},
        {"glProgramUniformMatrix4dv", pnames2069, '.', "...B."},
        {"glProgramUniformMatrix4dvEXT", pnames2070, '.', "...B."},
        {"glProgramUniformMatrix4fv", pnames2071, '.', "...B."},
        {"glProgramUniformMatrix4fvEXT", pnames2072, '.', "...B."},
        {"glProgramUniformMatrix4x2dv", pnames2073, '.', "...B."},
        {"glProgramUniformMatrix4x2dvEXT", pnames2074, '.', "...B."},
        {"glProgramUniformMatrix4x2fv", pnames2075, '.', "...B."},
        {"glProgramUniformMatrix4x2fvEXT", pnames2076, '.', "...B."},
        {"glProgramUniformMatrix4x3dv", pnames2077, '.', "...B."},
        {"glProgramUniformMatrix4x3dvEXT", pnames2078, '.', "...B."},
        {"glProgramUniformMatrix4x3fv", pnames2079, '.', "...B."},
        {"glProgramUniformMatrix4x3fvEXT", pnames2080, '.', "...B."},
        {"glProgramUniformui64NV", pnames2081, '.', "..."},
        {"glProgramUniformui64vNV", pnames2082, '.', "...."},
        {"glProgramVertexLimitNV", pnames2083, '.', "E."},
        {"glProvokingVertex", pnames2084, '.', "E"},
        {"glProvokingVertexEXT", pnames2085, '.', "E"},
        {"glPushAttrib", pnames2086, '.', "F"},
        {"glPushClientAttrib", pnames2087, '.', "F"},
        {"glPushClientAttribDefaultEXT", pnames2088, '.', "F"},
        {"glPushDebugGroup", pnames2089, '.', "E..."},
        {"glPushDebugGroupKHR", pnames2090, '.', "E..."},
        {"glPushGroupMarkerEXT", pnames2091, '.', ".."},
        {"glPushMatrix", pnames2092, '.', ""},
        {"glPushName", pnames2093, '.', "."},
        {"glQueryCounter", pnames2094, '.', ".E"},
        {"glQueryCounterEXT", pnames2095, '.', ".E"},
        {"glQueryMatrixxOES", pnames2096, 'F', ".."},
        {"glQueryObjectParameteruiAMD", pnames2097, '.', "E.E."},
        {"glRasterPos2d", pnames2098, '.', ".."},
        {"glRasterPos2dv", pnames2099, '.', "."},
        {"glRasterPos2f", pnames2100, '.', ".."},
        {"glRasterPos2fv", pnames2101, '.', "."},
        {"glRasterPos2i", pnames2102, '.', ".."},
        {"glRasterPos2iv", pnames2103, '.', "."},
        {"glRasterPos2s", pnames2104, '.', ".."},
        {"glRasterPos2sv", pnames2105, '.', "."},
        {"glRasterPos2xOES", pnames2106, '.', ".."},
        {"glRasterPos2xvOES", pnames2107, '.', "."},
        {"glRasterPos3d", pnames2108, '.', "..."},
        {"glRasterPos3dv", pnames2109, '.', "."},
        {"glRasterPos3f", pnames2110, '.', "..."},
        {"glRasterPos3fv", pnames2111, '.', "."},
        {"glRasterPos3i", pnames2112, '.', "..."},
        {"glRasterPos3iv", pnames2113, '.', "."},
        {"glRasterPos3s", pnames2114, '.', "..."},
        {"glRasterPos3sv", pnames2115, '.', "."},
        {"glRasterPos3xOES", pnames2116, '.', "..."},
        {"glRasterPos3xvOES", pnames2117, '.', "."},
        {"glRasterPos4d", pnames2118, '.', "...."},
        {"glRasterPos4dv", pnames2119, '.', "."},
        {"glRasterPos4f", pnames2120, '.', "...."},
        {"glRasterPos4fv", pnames2121, '.', "."},
        {"glRasterPos4i", pnames2122, '.', "...."},
        {"glRasterPos4iv", pnames2123, '.', "."},
        {"glRasterPos4s", pnames2124, '.', "...."},
        {"glRasterPos4sv", pnames2125, '.', "."},
        {"glRasterPos4xOES", pnames2126, '.', "...."},
        {"glRasterPos4xvOES", pnames2127, '.', "."},
        {"glRasterSamplesEXT", pnames2128, '.', ".B"},
        {"glReadBuffer", pnames2129, '.', "E"},
        {"glReadBufferIndexedEXT", pnames2130, '.', "E."},
        {"glReadBufferNV", pnames2131, '.', "E"},
        {"glReadInstrumentsSGIX", pnames2132, '.', "."},
        {"glReadPixels", pnames2133, '.', "....EE."},
        {"glReadnPixels", pnames2134, '.', "....EE.."},
        {"glReadnPixelsARB", pnames2135, '.', "....EE.."},
        {"glReadnPixelsEXT", pnames2136, '.', "....EE.."},
        {"glReadnPixelsKHR", pnames2137, '.', "....EE.."},
        {"glRectd", pnames2138, '.', "...."},
        {"glRectdv", pnames2139, '.', ".."},
        {"glRectf", pnames2140, '.', "...."},
        {"glRectfv", pnames2141, '.', ".."},
        {"glRecti", pnames2142, '.', "...."},
        {"glRectiv", pnames2143, '.', ".."},
        {"glRects", pnames2144, '.', "...."},
        {"glRectsv", pnames2145, '.', ".."},
        {"glRectxOES", pnames2146, '.', "...."},
        {"glRectxvOES", pnames2147, '.', ".."},
        {"glReferencePlaneSGIX", pnames2148, '.', "."},
        {"glReleaseShaderCompiler", pnames2149, '.', ""},
        {"glRenderMode", pnames2150, '.', "E"},
        {"glRenderbufferStorage", pnames2151, '.', "EE.."},
        {"glRenderbufferStorageEXT", pnames2152, '.', "EE.."},
        {"glRenderbufferStorageMultisample", pnames2153, '.', "E.E.."},
        {"glRenderbufferStorageMultisampleANGLE", pnames2154, '.', "E.E.."},
        {"glRenderbufferStorageMultisampleAPPLE", pnames2155, '.', "E.E.."},
        {"glRenderbufferStorageMultisampleCoverageNV", pnames2156, '.', "E..E.."},
        {"glRenderbufferStorageMultisampleEXT", pnames2157, '.', "E.E.."},
        {"glRenderbufferStorageMultisampleIMG", pnames2158, '.', "E.E.."},
        {"glRenderbufferStorageMultisampleNV", pnames2159, '.', "E.E.."},
        {"glRenderbufferStorageOES", pnames2160, '.', "EE.."},
        {"glReplacementCodePointerSUN", pnames2161, '.', "E.."},
        {"glReplacementCodeubSUN", pnames2162, '.', "."},
        {"glReplacementCodeubvSUN", pnames2163, '.', "."},
        {"glReplacementCodeuiColor3fVertex3fSUN", pnames2164, '.', "......."},
        {"glReplacementCodeuiColor3fVertex3fvSUN", pnames2165, '.', "..."},
        {"glReplacementCodeuiColor4fNormal3fVertex3fSUN", pnames2166, '.', "..........."},
        {"glReplacementCodeuiColor4fNormal3fVertex3fvSUN", pnames2167, '.', "...."},
        {"glReplacementCodeuiColor4ubVertex3fSUN", pnames2168, '.', "........"},
        {"glReplacementCodeuiColor4ubVertex3fvSUN", pnames2169, '.', "..."},
        {"glReplacementCodeuiNormal3fVertex3fSUN", pnames2170, '.', "......."},
        {"glReplacementCodeuiNormal3fVertex3fvSUN", pnames2171, '.', "..."},
        {"glReplacementCodeuiSUN", pnames2172, '.', "."},
        {"glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fSUN", pnames2173, '.', "............."},
        {"glReplacementCodeuiTexCoord2fColor4fNormal3fVertex3fvSUN", pnames2174, '.', "....."},
        {"glReplacementCodeuiTexCoord2fNormal3fVertex3fSUN", pnames2175, '.', "........."},
        {"glReplacementCodeuiTexCoord2fNormal3fVertex3fvSUN", pnames2176, '.', "...."},
        {"glReplacementCodeuiTexCoord2fVertex3fSUN", pnames2177, '.', "......"},
        {"glReplacementCodeuiTexCoord2fVertex3fvSUN", pnames2178, '.', "..."},
        {"glReplacementCodeuiVertex3fSUN", pnames2179, '.', "...."},
        {"glReplacementCodeuiVertex3fvSUN", pnames2180, '.', ".."},
        {"glReplacementCodeuivSUN", pnames2181, '.', "."},
        {"glReplacementCodeusSUN", pnames2182, '.', "."},
        {"glReplacementCodeusvSUN", pnames2183, '.', "."},
        {"glRequestResidentProgramsNV", pnames2184, '.', ".."},
        {"glResetHistogram", pnames2185, '.', "E"},
        {"glResetHistogramEXT", pnames2186, '.', "E"},
        {"glResetMinmax", pnames2187, '.', "E"},
        {"glResetMinmaxEXT", pnames2188, '.', "E"},
        {"glResizeBuffersMESA", pnames2189, '.', ""},
        {"glResolveDepthValuesNV", pnames2190, '.', ""},
        {"glResolveMultisampleFramebufferAPPLE", pnames2191, '.', ""},
        {"glResumeTransformFeedback", pnames2192, '.', ""},
        {"glResumeTransformFeedbackNV", pnames2193, '.', ""},
        {"glRotated", pnames2194, '.', "...."},
        {"glRotatef", pnames2195, '.', "...."},
        {"glRotatex", pnames2196, '.', "...."},
        {"glRotatexOES", pnames2197, '.', "...."},
        {"glSampleCoverage", pnames2198, '.', ".B"},
        {"glSampleCoverageARB", pnames2199, '.', ".B"},
        {"glSampleCoveragex", pnames2200, '.', ".B"},
        {"glSampleCoveragexOES", pnames2201, '.', ".B"},
        {"glSampleMapATI", pnames2202, '.', "..E"},
        {"glSampleMaskEXT", pnames2203, '.', ".B"},
        {"glSampleMaskIndexedNV", pnames2204, '.', ".F"},
        {"glSampleMaskSGIS", pnames2205, '.', ".B"},
        {"glSampleMaski", pnames2206, '.', ".F"},
        {"glSamplePatternEXT", pnames2207, '.', "E"},
        {"glSamplePatternSGIS", pnames2208, '.', "E"},
        {"glSamplerParameterIiv", pnames2209, '.', ".E."},
        {"glSamplerParameterIivEXT", pnames2210, '.', ".E."},
        {"glSamplerParameterIivOES", pnames2211, '.', ".E."},
        {"glSamplerParameterIuiv", pnames2212, '.', ".E."},
        {"glSamplerParameterIuivEXT", pnames2213, '.', ".E."},
        {"glSamplerParameterIuivOES", pnames2214, '.', ".E."},
        {"glSamplerParameterf", pnames2215, '.', ".E."},
        {"glSamplerParameterfv", pnames2216, '.', ".E."},
        {"glSamplerParameteri", pnames2217, '.', ".E."},
        {"glSamplerParameteriv", pnames2218, '.', ".E."},
        {"glScaled", pnames2219, '.', "..."},
        {"glScalef", pnames2220, '.', "..."},
        {"glScalex", pnames2221, '.', "..."},
        {"glScalexOES", pnames2222, '.', "..."},
        {"glScissor", pnames2223, '.', "...."},
        {"glScissorArrayv", pnames2224, '.', "..."},
        {"glScissorArrayvNV", pnames2225, '.', "..."},
        {"glScissorArrayvOES", pnames2226, '.', "..."},
        {"glScissorIndexed", pnames2227, '.', "....."},
        {"glScissorIndexedNV", pnames2228, '.', "....."},
        {"glScissorIndexedOES", pnames2229, '.', "....."},
        {"glScissorIndexedv", pnames2230, '.', ".."},
        {"glScissorIndexedvNV", pnames2231, '.', ".."},
        {"glScissorIndexedvOES", pnames2232, '.', ".."},
        {"glSecondaryColor3b", pnames2233, '.', "..."},
        {"glSecondaryColor3bEXT", pnames2234, '.', "..."},
        {"glSecondaryColor3bv", pnames2235, '.', "."},
        {"glSecondaryColor3bvEXT", pnames2236, '.', "."},
        {"glSecondaryColor3d", pnames2237, '.', "..."},
        {"glSecondaryColor3dEXT", pnames2238, '.', "..."},
        {"glSecondaryColor3dv", pnames2239, '.', "."},
        {"glSecondaryColor3dvEXT", pnames2240, '.', "."},
        {"glSecondaryColor3f", pnames2241, '.', "..."},
        {"glSecondaryColor3fEXT", pnames2242, '.', "..."},
        {"glSecondaryColor3fv", pnames2243, '.', "."},
        {"glSecondaryColor3fvEXT", pnames2244, '.', "."},
        {"glSecondaryColor3hNV", pnames2245, '.', "..."},
        {"glSecondaryColor3hvNV", pnames2246, '.', "."},
        {"glSecondaryColor3i", pnames2247, '.', "..."},
        {"glSecondaryColor3iEXT", pnames2248, '.', "..."},
        {"glSecondaryColor3iv", pnames2249, '.', "."},
        {"glSecondaryColor3ivEXT", pnames2250, '.', "."},
        {"glSecondaryColor3s", pnames2251, '.', "..."},
        {"glSecondaryColor3sEXT", pnames2252, '.', "..."},
        {"glSecondaryColor3sv", pnames2253, '.', "."},
        {"glSecondaryColor3svEXT", pnames2254, '.', "."},
        {"glSecondaryColor3ub", pnames2255, '.', "..."},
        {"glSecondaryColor3ubEXT", pnames2256, '.', "..."},
        {"glSecondaryColor3ubv", pnames2257, '.', "."},
        {"glSecondaryColor3ubvEXT", pnames2258, '.', "."},
        {"glSecondaryColor3ui", pnames2259, '.', "..."},
        {"glSecondaryColor3uiEXT", pnames2260, '.', "..."},
        {"glSecondaryColor3uiv", pnames2261, '.', "."},
        {"glSecondaryColor3uivEXT", pnames2262, '.', "."},
        {"glSecondaryColor3us", pnames2263, '.', "..."},
        {"glSecondaryColor3usEXT", pnames2264, '.', "..."},
        {"glSecondaryColor3usv", pnames2265, '.', "."},
        {"glSecondaryColor3usvEXT", pnames2266, '.', "."},
        {"glSecondaryColorFormatNV", pnames2267, '.', ".E."},
        {"glSecondaryColorP3ui", pnames2268, '.', "E."},
        {"glSecondaryColorP3uiv", pnames2269, '.', "E."},
        {"glSecondaryColorPointer", pnames2270, '.', ".E.."},
        {"glSecondaryColorPointerEXT", pnames2271, '.', ".E.."},
        {"glSecondaryColorPointerListIBM", pnames2272, '.', ".E..."},
        {"glSelectBuffer", pnames2273, '.', ".."},
        {"glSelectPerfMonitorCountersAMD", pnames2274, '.', ".B..."},
        {"glSeparableFilter2D", pnames2275, '.', "EE..EE.."},
        {"glSeparableFilter2DEXT", pnames2276, '.', "EE..EE.."},
        {"glSetFenceAPPLE", pnames2277, '.', "."},
        {"glSetFenceNV", pnames2278, '.', ".E"},
        {"glSetFragmentShaderConstantATI", pnames2279, '.', ".."},
        {"glSetInvariantEXT", pnames2280, '.', ".E."},
        {"glSetLocalConstantEXT", pnames2281, '.', ".E."},
        {"glSetMultisamplefvAMD", pnames2282, '.', "E.."},
        {"glShadeModel", pnames2283, '.', "E"},
        {"glShaderBinary", pnames2284, '.', "..E.."},
        {"glShaderOp1EXT", pnames2285, '.', "E.."},
        {"glShaderOp2EXT", pnames2286, '.', "E..."},
        {"glShaderOp3EXT", pnames2287, '.', "E...."},
        {"glShaderSource", pnames2288, '.', "...."},
        {"glShaderSourceARB", pnames2289, '.', "...."},
        {"glShaderStorageBlockBinding", pnames2290, '.', "..."},
        {"glSharpenTexFuncSGIS", pnames2291, '.', "E.."},
        {"glSpriteParameterfSGIX", pnames2292, '.', "E."},
        {"glSpriteParameterfvSGIX", pnames2293, '.', "E."},
        {"glSpriteParameteriSGIX", pnames2294, '.', "E."},
        {"glSpriteParameterivSGIX", pnames2295, '.', "E."},
        {"glStartInstrumentsSGIX", pnames2296, '.', ""},
        {"glStartTilingQCOM", pnames2297, '.', "....F"},
        {"glStateCaptureNV", pnames2298, '.', ".E"},
        {"glStencilClearTagEXT", pnames2299, '.', ".."},
        {"glStencilFillPathInstancedNV", pnames2300, '.', ".E..E.E."},
        {"glStencilFillPathNV", pnames2301, '.', ".E."},
        {"glStencilFunc", pnames2302, '.', "E.."},
        {"glStencilFuncSeparate", pnames2303, '.', "EE.."},
        {"glStencilFuncSeparateATI", pnames2304, '.', "EE.."},
        {"glStencilMask", pnames2305, '.', "."},
        {"glStencilMaskSeparate", pnames2306, '.', "E."},
        {"glStencilOp", pnames2307, '.', "EEE"},
        {"glStencilOpSeparate", pnames2308, '.', "EEEE"},
        {"glStencilOpSeparateATI", pnames2309, '.', "EEEE"},
        {"glStencilOpValueAMD", pnames2310, '.', "E."},
        {"glStencilStrokePathInstancedNV", pnames2311, '.', ".E....E."},
        {"glStencilStrokePathNV", pnames2312, '.', "..."},
        {"glStencilThenCoverFillPathInstancedNV", pnames2313, '.', ".E..E.EE."},
        {"glStencilThenCoverFillPathNV", pnames2314, '.', ".E.E"},
        {"glStencilThenCoverStrokePathInstancedNV", pnames2315, '.', ".E....EE."},
        {"glStencilThenCoverStrokePathNV", pnames2316, '.', "...E"},
        {"glStopInstrumentsSGIX", pnames2317, '.', "."},
        {"glStringMarkerGREMEDY", pnames2318, '.', ".."},
        {"glSubpixelPrecisionBiasNV", pnames2319, '.', ".."},
        {"glSwizzleEXT", pnames2320, '.', "..EEEE"},
        {"glSyncTextureINTEL", pnames2321, '.', "."},
        {"glTagSampleBufferSGIX", pnames2322, '.', ""},
        {"glTangent3bEXT", pnames2323, '.', "..."},
        {"glTangent3bvEXT", pnames2324, '.', "."},
        {"glTangent3dEXT", pnames2325, '.', "..."},
        {"glTangent3dvEXT", pnames2326, '.', "."},
        {"glTangent3fEXT", pnames2327, '.', "..."},
        {"glTangent3fvEXT", pnames2328, '.', "."},
        {"glTangent3iEXT", pnames2329, '.', "..."},
        {"glTangent3ivEXT", pnames2330, '.', "."},
        {"glTangent3sEXT", pnames2331, '.', "..."},
        {"glTangent3svEXT", pnames2332, '.', "."},
        {"glTangentPointerEXT", pnames2333, '.', "E.."},
        {"glTbufferMask3DFX", pnames2334, '.', "."},
        {"glTessellationFactorAMD", pnames2335, '.', "."},
        {"glTessellationModeAMD", pnames2336, '.', "E"},
        {"glTestFenceAPPLE", pnames2337, 'B', "."},
        {"glTestFenceNV", pnames2338, 'B', "."},
        {"glTestObjectAPPLE", pnames2339, 'B', "E."},
        {"glTexBuffer", pnames2340, '.', "EE."},
        {"glTexBufferARB", pnames2341, '.', "EE."},
        {"glTexBufferEXT", pnames2342, '.', "EE."},
        {"glTexBufferOES", pnames2343, '.', "EE."},
        {"glTexBufferRange", pnames2344, '.', "EE..."},
        {"glTexBufferRangeEXT", pnames2345, '.', "EE..."},
        {"glTexBufferRangeOES", pnames2346, '.', "EE..."},
        {"glTexBumpParameterfvATI", pnames2347, '.', "E."},
        {"glTexBumpParameterivATI", pnames2348, '.', "E."},
        {"glTexCoord1bOES", pnames2349, '.', "."},
        {"glTexCoord1bvOES", pnames2350, '.', "."},
        {"glTexCoord1d", pnames2351, '.', "."},
        {"glTexCoord1dv", pnames2352, '.', "."},
        {"glTexCoord1f", pnames2353, '.', "."},
        {"glTexCoord1fv", pnames2354, '.', "."},
        {"glTexCoord1hNV", pnames2355, '.', "."},
        {"glTexCoord1hvNV", pnames2356, '.', "."},
        {"glTexCoord1i", pnames2357, '.', "."},
        {"glTexCoord1iv", pnames2358, '.', "."},
        {"glTexCoord1s", pnames2359, '.', "."},
        {"glTexCoord1sv", pnames2360, '.', "."},
        {"glTexCoord1xOES", pnames2361, '.', "."},
        {"glTexCoord1xvOES", pnames2362, '.', "."},
        {"glTexCoord2bOES", pnames2363, '.', ".."},
        {"glTexCoord2bvOES", pnames2364, '.', "."},
        {"glTexCoord2d", pnames2365, '.', ".."},
        {"glTexCoord2dv", pnames2366, '.', "."},
        {"glTexCoord2f", pnames2367, '.', ".."},
        {"glTexCoord2fColor3fVertex3fSUN", pnames2368, '.', "........"},
        {"glTexCoord2fColor3fVertex3fvSUN", pnames2369, '.', "..."},
        {"glTexCoord2fColor4fNormal3fVertex3fSUN", pnames2370, '.', "............"},
        {"glTexCoord2fColor4fNormal3fVertex3fvSUN", pnames2371, '.', "...."},
        {"glTexCoord2fColor4ubVertex3fSUN", pnames2372, '.', "........."},
        {"glTexCoord2fColor4ubVertex3fvSUN", pnames2373, '.', "..."},
        {"glTexCoord2fNormal3fVertex3fSUN", pnames2374, '.', "........"},
        {"glTexCoord2fNormal3fVertex3fvSUN", pnames2375, '.', "..."},
        {"glTexCoord2fVertex3fSUN", pnames2376, '.', "....."},
        {"glTexCoord2fVertex3fvSUN", pnames2377, '.', ".."},
        {"glTexCoord2fv", pnames2378, '.', "."},
        {"glTexCoord2hNV", pnames2379, '.', ".."},
        {"glTexCoord2hvNV", pnames2380, '.', "."},
        {"glTexCoord2i", pnames2381, '.', ".."},
        {"glTexCoord2iv", pnames2382, '.', "."},
        {"glTexCoord2s", pnames2383, '.', ".."},
        {"glTexCoord2sv", pnames2384, '.', "."},
        {"glTexCoord2xOES", pnames2385, '.', ".."},
        {"glTexCoord2xvOES", pnames2386, '.', "."},
        {"glTexCoord3bOES", pnames2387, '.', "..."},
        {"glTexCoord3bvOES", pnames2388, '.', "."},
        {"glTexCoord3d", pnames2389, '.', "..."},
        {"glTexCoord3dv", pnames2390, '.', "."},
        {"glTexCoord3f", pnames2391, '.', "..."},
        {"glTexCoord3fv", pnames2392, '.', "."},
        {"glTexCoord3hNV", pnames2393, '.', "..."},
        {"glTexCoord3hvNV", pnames2394, '.', "."},
        {"glTexCoord3i", pnames2395, '.', "..."},
        {"glTexCoord3iv", pnames2396, '.', "."},
        {"glTexCoord3s", pnames2397, '.', "..."},
        {"glTexCoord3sv", pnames2398, '.', "."},
        {"glTexCoord3xOES", pnames2399, '.', "..."},
        {"glTexCoord3xvOES", pnames2400, '.', "."},
        {"glTexCoord4bOES", pnames2401, '.', "...."},
        {"glTexCoord4bvOES", pnames2402, '.', "."},
        {"glTexCoord4d", pnames2403, '.', "...."},
        {"glTexCoord4dv", pnames2404, '.', "."},
        {"glTexCoord4f", pnames2405, '.', "...."},
        {"glTexCoord4fColor4fNormal3fVertex4fSUN", pnames2406, '.', "..............."},
        {"glTexCoord4fColor4fNormal3fVertex4fvSUN", pnames2407, '.', "...."},
        {"glTexCoord4fVertex4fSUN", pnames2408, '.', "........"},
        {"glTexCoord4fVertex4fvSUN", pnames2409, '.', ".."},
        {"glTexCoord4fv", pnames2410, '.', "."},
        {"glTexCoord4hNV", pnames2411, '.', "...."},
        {"glTexCoord4hvNV", pnames2412, '.', "."},
        {"glTexCoord4i", pnames2413, '.', "...."},
        {"glTexCoord4iv", pnames2414, '.', "."},
        {"glTexCoord4s", pnames2415, '.', "...."},
        {"glTexCoord4sv", pnames2416, '.', "."},
        {"glTexCoord4xOES", pnames2417, '.', "...."},
        {"glTexCoord4xvOES", pnames2418, '.', "."},
        {"glTexCoordFormatNV", pnames2419, '.', ".E."},
        {"glTexCoordP1ui", pnames2420, '.', "E."},
        {"glTexCoordP1uiv", pnames2421, '.', "E."},
        {"glTexCoordP2ui", pnames2422, '.', "E."},
        {"glTexCoordP2uiv", pnames2423, '.', "E."},
        {"glTexCoordP3ui", pnames2424, '.', "E."},
        {"glTexCoordP3uiv", pnames2425, '.', "E."},
        {"glTexCoordP4ui", pnames2426, '.', "E."},
        {"glTexCoordP4uiv", pnames2427, '.', "E."},
        {"glTexCoordPointer", pnames2428, '.', ".E.."},
        {"glTexCoordPointerEXT", pnames2429, '.', ".E..."},
        {"glTexCoordPointerListIBM", pnames2430, '.', ".E..."},
        {"glTexCoordPointervINTEL", pnames2431, '.', ".E."},
        {"glTexEnvf", pnames2432, '.', "EE."},
        {"glTexEnvfv", pnames2433, '.', "EE."},
        {"glTexEnvi", pnames2434, '.', "EE."},
        {"glTexEnviv", pnames2435, '.', "EE."},
        {"glTexEnvx", pnames2436, '.', "EE."},
        {"glTexEnvxOES", pnames2437, '.', "EE."},
        {"glTexEnvxv", pnames2438, '.', "EE."},
        {"glTexEnvxvOES", pnames2439, '.', "EE."},
        {"glTexFilterFuncSGIS", pnames2440, '.', "EE.."},
        {"glTexGend", pnames2441, '.', "EE."},
        {"glTexGendv", pnames2442, '.', "EE."},
        {"glTexGenf", pnames2443, '.', "EE."},
        {"glTexGenfOES", pnames2444, '.', "EE."},
        {"glTexGenfv", pnames2445, '.', "EE."},
        {"glTexGenfvOES", pnames2446, '.', "EE."},
        {"glTexGeni", pnames2447, '.', "EE."},
        {"glTexGeniOES", pnames2448, '.', "EE."},
        {"glTexGeniv", pnames2449, '.', "EE."},
        {"glTexGenivOES", pnames2450, '.', "EE."},
        {"glTexGenxOES", pnames2451, '.', "EE."},
        {"glTexGenxvOES", pnames2452, '.', "EE."},
        {"glTexImage1D", pnames2453, '.', "E....EE."},
        {"glTexImage2D", pnames2454, '.', "E.....EE."},
        {"glTexImage2DMultisample", pnames2455, '.', "E.E..B"},
        {"glTexImage2DMultisampleCoverageNV", pnames2456, '.', "E.....B"},
        {"glTexImage3D", pnames2457, '.', "E......EE."},
        {"glTexImage3DEXT", pnames2458, '.', "E.E....EE."},
        {"glTexImage3DMultisample", pnames2459, '.', "E.E...B"},
        {"glTexImage3DMultisampleCoverageNV", pnames2460, '.', "E......B"},
        {"glTexImage3DOES", pnames2461, '.', "E.E....EE."},
        {"glTexImage4DSGIS", pnames2462, '.', "E.E.....EE."},
        {"glTexPageCommitmentARB", pnames2463, '.', "E.......B"},
        {"glTexPageCommitmentEXT", pnames2464, '.', "E.......B"},
        {"glTexParameterIiv", pnames2465, '.', "EE."},
        {"glTexParameterIivEXT", pnames2466, '.', "EE."},
        {"glTexParameterIivOES", pnames2467, '.', "EE."},
        {"glTexParameterIuiv", pnames2468, '.', "EE."},
        {"glTexParameterIuivEXT", pnames2469, '.', "EE."},
        {"glTexParameterIuivOES", pnames2470, '.', "EE."},
        {"glTexParameterf", pnames2471, '.', "EE."},
        {"glTexParameterfv", pnames2472, '.', "EE."},
        {"glTexParameteri", pnames2473, '.', "EE."},
        {"glTexParameteriv", pnames2474, '.', "EE."},
        {"glTexParameterx", pnames2475, '.', "EE."},
        {"glTexParameterxOES", pnames2476, '.', "EE."},
        {"glTexParameterxv", pnames2477, '.', "EE."},
        {"glTexParameterxvOES", pnames2478, '.', "EE."},
        {"glTexRenderbufferNV", pnames2479, '.', "E."},
        {"glTexStorage1D", pnames2480, '.', "E.E."},
        {"glTexStorage1DEXT", pnames2481, '.', "E.E."},
        {"glTexStorage2D", pnames2482, '.', "E.E.."},
        {"glTexStorage2DEXT", pnames2483, '.', "E.E.."},
        {"glTexStorage2DMultisample", pnames2484, '.', "E.E..B"},
        {"glTexStorage3D", pnames2485, '.', "E.E..."},
        {"glTexStorage3DEXT", pnames2486, '.', "E.E..."},
        {"glTexStorage3DMultisample", pnames2487, '.', "E.E...B"},
        {"glTexStorage3DMultisampleOES", pnames2488, '.', "E.E...B"},
        {"glTexStorageSparseAMD", pnames2489, '.', "EE....F"},
        {"glTexSubImage1D", pnames2490, '.', "E...EE."},
        {"glTexSubImage1DEXT", pnames2491, '.', "E...EE."},
        {"glTexSubImage2D", pnames2492, '.', "E.....EE."},
        {"glTexSubImage2DEXT", pnames2493, '.', "E.....EE."},
        {"glTexSubImage3D", pnames2494, '.', "E.......EE."},
        {"glTexSubImage3DEXT", pnames2495, '.', "E.......EE."},
        {"glTexSubImage3DOES", pnames2496, '.', "E.......EE."},
        {"glTexSubImage4DSGIS", pnames2497, '.', "E.........EE."},
        {"glTextureBarrier", pnames2498, '.', ""},
        {"glTextureBarrierNV", pnames2499, '.', ""},
        {"glTextureBuffer", pnames2500, '.', ".E."},
        {"glTextureBufferEXT", pnames2501, '.', ".EE."},
        {"glTextureBufferRange", pnames2502, '.', ".E..."},
        {"glTextureBufferRangeEXT", pnames2503, '.', ".EE..."},
        {"glTextureColorMaskSGIS", pnames2504, '.', "BBBB"},
        {"glTextureImage1DEXT", pnames2505, '.', ".E....EE."},
        {"glTextureImage2DEXT", pnames2506, '.', ".E.....EE."},
        {"glTextureImage2DMultisampleCoverageNV", pnames2507, '.', ".E.....B"},
        {"glTextureImage2DMultisampleNV", pnames2508, '.', ".E....B"},
        {"glTextureImage3DEXT", pnames2509, '.', ".E......EE."},
        {"glTextureImage3DMultisampleCoverageNV", pnames2510, '.', ".E......B"},
        {"glTextureImage3DMultisampleNV", pnames2511, '.', ".E.....B"},
        {"glTextureLightEXT", pnames2512, '.', "E"},
        {"glTextureMaterialEXT", pnames2513, '.', "EE"},
        {"glTextureNormalEXT", pnames2514, '.', "E"},
        {"glTexturePageCommitmentEXT", pnames2515, '.', "........B"},
        {"glTextureParameterIiv", pnames2516, '.', ".E."},
        {"glTextureParameterIivEXT", pnames2517, '.', ".EE."},
        {"glTextureParameterIuiv", pnames2518, '.', ".E."},
        {"glTextureParameterIuivEXT", pnames2519, '.', ".EE."},
        {"glTextureParameterf", pnames2520, '.', ".E."},
        {"glTextureParameterfEXT", pnames2521, '.', ".EE."},
        {"glTextureParameterfv", pnames2522, '.', ".E."},
        {"glTextureParameterfvEXT", pnames2523, '.', ".EE."},
        {"glTextureParameteri", pnames2524, '.', ".E."},
        {"glTextureParameteriEXT", pnames2525, '.', ".EE."},
        {"glTextureParameteriv", pnames2526, '.', ".E."},
        {"glTextureParameterivEXT", pnames2527, '.', ".EE."},
        {"glTextureRangeAPPLE", pnames2528, '.', "E.."},
        {"glTextureRenderbufferEXT", pnames2529, '.', ".E."},
        {"glTextureStorage1D", pnames2530, '.', "..E."},
        {"glTextureStorage1DEXT", pnames2531, '.', ".E.E."},
        {"glTextureStorage2D", pnames2532, '.', "..E.."},
        {"glTextureStorage2DEXT", pnames2533, '.', ".E.E.."},
        {"glTextureStorage2DMultisample", pnames2534, '.', "..E..B"},
        {"glTextureStorage2DMultisampleEXT", pnames2535, '.', ".E.E..B"},
        {"glTextureStorage3D", pnames2536, '.', "..E..."},
        {"glTextureStorage3DEXT", pnames2537, '.', ".E.E..."},
        {"glTextureStorage3DMultisample", pnames2538, '.', "..E...B"},
        {"glTextureStorage3DMultisampleEXT", pnames2539, '.', ".E.E...B"},
        {"glTextureStorageSparseAMD", pnames2540, '.', ".EE....F"},
        {"glTextureSubImage1D", pnames2541, '.', "....EE."},
        {"glTextureSubImage1DEXT", pnames2542, '.', ".E...EE."},
        {"glTextureSubImage2D", pnames2543, '.', "......EE."},
        {"glTextureSubImage2DEXT", pnames2544, '.', ".E.....EE."},
        {"glTextureSubImage3D", pnames2545, '.', "........EE."},
        {"glTextureSubImage3DEXT", pnames2546, '.', ".E.......EE."},
        {"glTextureView", pnames2547, '.', ".E.E...."},
        {"glTextureViewEXT", pnames2548, '.', ".E.E...."},
        {"glTextureViewOES", pnames2549, '.', ".E.E...."},
        {"glTrackMatrixNV", pnames2550, '.', "E.EE"},
        {"glTransformFeedbackAttribsNV", pnames2551, '.', "..E"},
        {"glTransformFeedbackBufferBase", pnames2552, '.', "..."},
        {"glTransformFeedbackBufferRange", pnames2553, '.', "....."},
        {"glTransformFeedbackStreamAttribsNV", pnames2554, '.', "....E"},
        {"glTransformFeedbackVaryings", pnames2555, '.', "...E"},
        {"glTransformFeedbackVaryingsEXT", pnames2556, '.', "...E"},
        {"glTransformFeedbackVaryingsNV", pnames2557, '.', "...E"},
        {"glTransformPathNV", pnames2558, '.', "..E."},
        {"glTranslated", pnames2559, '.', "..."},
        {"glTranslatef", pnames2560, '.', "..."},
        {"glTranslatex", pnames2561, '.', "..."},
        {"glTranslatexOES", pnames2562, '.', "..."},
        {"glUniform1d", pnames2563, '.', ".."},
        {"glUniform1dv", pnames2564, '.', "..."},
        {"glUniform1f", pnames2565, '.', ".."},
        {"glUniform1fARB", pnames2566, '.', ".."},
        {"glUniform1fv", pnames2567, '.', "..."},
        {"glUniform1fvARB", pnames2568, '.', "..."},
        {"glUniform1i", pnames2569, '.', ".."},
        {"glUniform1i64ARB", pnames2570, '.', ".."},
        {"glUniform1i64NV", pnames2571, '.', ".."},
        {"glUniform1i64vARB", pnames2572, '.', "..."},
        {"glUniform1i64vNV", pnames2573, '.', "..."},
        {"glUniform1iARB", pnames2574, '.', ".."},
        {"glUniform1iv", pnames2575, '.', "..."},
        {"glUniform1ivARB", pnames2576, '.', "..."},
        {"glUniform1ui", pnames2577, '.', ".."},
        {"glUniform1ui64ARB", pnames2578, '.', ".."},
        {"glUniform1ui64NV", pnames2579, '.', ".."},
        {"glUniform1ui64vARB", pnames2580, '.', "..."},
        {"glUniform1ui64vNV", pnames2581, '.', "..."},
        {"glUniform1uiEXT", pnames2582, '.', ".."},
        {"glUniform1uiv", pnames2583, '.', "..."},
        {"glUniform1uivEXT", pnames2584, '.', "..."},
        {"glUniform2d", pnames2585, '.', "..."},
        {"glUniform2dv", pnames2586, '.', "..."},
        {"glUniform2f", pnames2587, '.', "..."},
        {"glUniform2fARB", pnames2588, '.', "..."},
        {"glUniform2fv", pnames2589, '.', "..."},
        {"glUniform2fvARB", pnames2590, '.', "..."},
        {"glUniform2i", pnames2591, '.', "..."},
        {"glUniform2i64ARB", pnames2592, '.', "..."},
        {"glUniform2i64NV", pnames2593, '.', "..."},
        {"glUniform2i64vARB", pnames2594, '.', "..."},
        {"glUniform2i64vNV", pnames2595, '.', "..."},
        {"glUniform2iARB", pnames2596, '.', "..."},
        {"glUniform2iv", pnames2597, '.', "..."},
        {"glUniform2ivARB", pnames2598, '.', "..."},
        {"glUniform2ui", pnames2599, '.', "..."},
        {"glUniform2ui64ARB", pnames2600, '.', "..."},
        {"glUniform2ui64NV", pnames2601, '.', "..."},
        {"glUniform2ui64vARB", pnames2602, '.', "..."},
        {"glUniform2ui64vNV", pnames2603, '.', "..."},
        {"glUniform2uiEXT", pnames2604, '.', "..."},
        {"glUniform2uiv", pnames2605, '.', "..."},
        {"glUniform2uivEXT", pnames2606, '.', "..."},
        {"glUniform3d", pnames2607, '.', "...."},
        {"glUniform3dv", pnames2608, '.', "..."},
        {"glUniform3f", pnames2609, '.', "...."},
        {"glUniform3fARB", pnames2610, '.', "...."},
        {"glUniform3fv", pnames2611, '.', "..."},
        {"glUniform3fvARB", pnames2612, '.', "..."},
        {"glUniform3i", pnames2613, '.', "...."},
        {"glUniform3i64ARB", pnames2614, '.', "...."},
        {"glUniform3i64NV", pnames2615, '.', "...."},
        {"glUniform3i64vARB", pnames2616, '.', "..."},
        {"glUniform3i64vNV", pnames2617, '.', "..."},
        {"glUniform3iARB", pnames2618, '.', "...."},
        {"glUniform3iv", pnames2619, '.', "..."},
        {"glUniform3ivARB", pnames2620, '.', "..."},
        {"glUniform3ui", pnames2621, '.', "...."},
        {"glUniform3ui64ARB", pnames2622, '.', "...."},
        {"glUniform3ui64NV", pnames2623, '.', "...."},
        {"glUniform3ui64vARB", pnames2624, '.', "..."},
        {"glUniform3ui64vNV", pnames2625, '.', "..."},
        {"glUniform3uiEXT", pnames2626, '.', "...."},
        {"glUniform3uiv", pnames2627, '.', "..."},
        {"glUniform3uivEXT", pnames2628, '.', "..."},
        {"glUniform4d", pnames2629, '.', "....."},
        {"glUniform4dv", pnames2630, '.', "..."},
        {"glUniform4f", pnames2631, '.', "....."},
        {"glUniform4fARB", pnames2632, '.', "....."},
        {"glUniform4fv", pnames2633, '.', "..."},
        {"glUniform4fvARB", pnames2634, '.', "..."},
        {"glUniform4i", pnames2635, '.', "....."},
        {"glUniform4i64ARB", pnames2636, '.', "....."},
        {"glUniform4i64NV", pnames2637, '.', "....."},
        {"glUniform4i64vARB", pnames2638, '.', "..."},
        {"glUniform4i64vNV", pnames2639, '.', "..."},
        {"glUniform4iARB", pnames2640, '.', "....."},
        {"glUniform4iv", pnames2641, '.', "..."},
        {"glUniform4ivARB", pnames2642, '.', "..."},
        {"glUniform4ui", pnames2643, '.', "....."},
        {"glUniform4ui64ARB", pnames2644, '.', "....."},
        {"glUniform4ui64NV", pnames2645, '.', "....."},
        {"glUniform4ui64vARB", pnames2646, '.', "..."},
        {"glUniform4ui64vNV", pnames2647, '.', "..."},
        {"glUniform4uiEXT", pnames2648, '.', "....."},
        {"glUniform4uiv", pnames2649, '.', "..."},
        {"glUniform4uivEXT", pnames2650, '.', "..."},
        {"glUniformBlockBinding", pnames2651, '.', "..."},
        {"glUniformBufferEXT", pnames2652, '.', "..."},
        {"glUniformHandleui64ARB", pnames2653, '.', ".."},
        {"glUniformHandleui64IMG", pnames2654, '.', ".."},
        {"glUniformHandleui64NV", pnames2655, '.', ".."},
        {"glUniformHandleui64vARB", pnames2656, '.', "..."},
        {"glUniformHandleui64vIMG", pnames2657, '.', "..."},
        {"glUniformHandleui64vNV", pnames2658, '.', "..."},
        {"glUniformMatrix2dv", pnames2659, '.', "..B."},
        {"glUniformMatrix2fv", pnames2660, '.', "..B."},
        {"glUniformMatrix2fvARB", pnames2661, '.', "..B."},
        {"glUniformMatrix2x3dv", pnames2662, '.', "..B."},
        {"glUniformMatrix2x3fv", pnames2663, '.', "..B."},
        {"glUniformMatrix2x3fvNV", pnames2664, '.', "..B."},
        {"glUniformMatrix2x4dv", pnames2665, '.', "..B."},
        {"glUniformMatrix2x4fv", pnames2666, '.', "..B."},
        {"glUniformMatrix2x4fvNV", pnames2667, '.', "..B."},
        {"glUniformMatrix3dv", pnames2668, '.', "..B."},
        {"glUniformMatrix3fv", pnames2669, '.', "..B."},
        {"glUniformMatrix3fvARB", pnames2670, '.', "..B."},
        {"glUniformMatrix3x2dv", pnames2671, '.', "..B."},
        {"glUniformMatrix3x2fv", pnames2672, '.', "..B."},
        {"glUniformMatrix3x2fvNV", pnames2673, '.', "..B."},
        {"glUniformMatrix3x4dv", pnames2674, '.', "..B."},
        {"glUniformMatrix3x4fv", pnames2675, '.', "..B."},
        {"glUniformMatrix3x4fvNV", pnames2676, '.', "..B."},
        {"glUniformMatrix4dv", pnames2677, '.', "..B."},
        {"glUniformMatrix4fv", pnames2678, '.', "..B."},
        {"glUniformMatrix4fvARB", pnames2679, '.', "..B."},
        {"glUniformMatrix4x2dv", pnames2680, '.', "..B."},
        {"glUniformMatrix4x2fv", pnames2681, '.', "..B."},
        {"glUniformMatrix4x2fvNV", pnames2682, '.', "..B."},
        {"glUniformMatrix4x3dv", pnames2683, '.', "..B."},
        {"glUniformMatrix4x3fv", pnames2684, '.', "..B."},
        {"glUniformMatrix4x3fvNV", pnames2685, '.', "..B."},
        {"glUniformSubroutinesuiv", pnames2686, '.', "E.."},
        {"glUniformui64NV", pnames2687, '.', ".."},
        {"glUniformui64vNV", pnames2688, '.', "..."},
        {"glUnlockArraysEXT", pnames2689, '.', ""},
        {"glUnmapBuffer", pnames2690, 'B', "E"},
        {"glUnmapBufferARB", pnames2691, 'B', "E"},
        {"glUnmapBufferOES", pnames2692, 'B', "E"},
        {"glUnmapNamedBuffer", pnames2693, 'B', "."},
        {"glUnmapNamedBufferEXT", pnames2694, 'B', "."},
        {"glUnmapObjectBufferATI", pnames2695, '.', "."},
        {"glUnmapTexture2DINTEL", pnames2696, '.', ".."},
        {"glUpdateObjectBufferATI", pnames2697, '.', "....E"},
        {"glUseProgram", pnames2698, '.', "."},
        {"glUseProgramObjectARB", pnames2699, '.', "."},
        {"glUseProgramStages", pnames2700, '.', ".F."},
        {"glUseProgramStagesEXT", pnames2701, '.', ".F."},
        {"glUseShaderProgramEXT", pnames2702, '.', "E."},
        {"glVDPAUFiniNV", pnames2703, '.', ""},
        {"glVDPAUGetSurfaceivNV", pnames2704, '.', ".E..."},
        {"glVDPAUInitNV", pnames2705, '.', ".."},
        {"glVDPAUIsSurfaceNV", pnames2706, 'B', "."},
        {"glVDPAUMapSurfacesNV", pnames2707, '.', ".."},
        {"glVDPAURegisterOutputSurfaceNV", pnames2708, '.', ".E.."},
        {"glVDPAURegisterVideoSurfaceNV", pnames2709, '.', ".E.."},
        {"glVDPAUSurfaceAccessNV", pnames2710, '.', ".E"},
        {"glVDPAUUnmapSurfacesNV", pnames2711, '.', ".."},
        {"glVDPAUUnregisterSurfaceNV", pnames2712, '.', "."},
        {"glValidateProgram", pnames2713, '.', "."},
        {"glValidateProgramARB", pnames2714, '.', "."},
        {"glValidateProgramPipeline", pnames2715, '.', "."},
        {"glValidateProgramPipelineEXT", pnames2716, '.', "."},
        {"glVariantArrayObjectATI", pnames2717, '.', ".E..."},
        {"glVariantPointerEXT", pnames2718, '.', ".E.."},
        {"glVariantbvEXT", pnames2719, '.', ".."},
        {"glVariantdvEXT", pnames2720, '.', ".."},
        {"glVariantfvEXT", pnames2721, '.', ".."},
        {"glVariantivEXT", pnames2722, '.', ".."},
        {"glVariantsvEXT", pnames2723, '.', ".."},
        {"glVariantubvEXT", pnames2724, '.', ".."},
        {"glVariantuivEXT", pnames2725, '.', ".."},
        {"glVariantusvEXT", pnames2726, '.', ".."},
        {"glVertex2bOES", pnames2727, '.', ".."},
        {"glVertex2bvOES", pnames2728, '.', "."},
        {"glVertex2d", pnames2729, '.', ".."},
        {"glVertex2dv", pnames2730, '.', "."},
        {"glVertex2f", pnames2731, '.', ".."},
        {"glVertex2fv", pnames2732, '.', "."},
        {"glVertex2hNV", pnames2733, '.', ".."},
        {"glVertex2hvNV", pnames2734, '.', "."},
        {"glVertex2i", pnames2735, '.', ".."},
        {"glVertex2iv", pnames2736, '.', "."},
        {"glVertex2s", pnames2737, '.', ".."},
        {"glVertex2sv", pnames2738, '.', "."},
        {"glVertex2xOES", pnames2739, '.', "."},
        {"glVertex2xvOES", pnames2740, '.', "."},
        {"glVertex3bOES", pnames2741, '.', "..."},
        {"glVertex3bvOES", pnames2742, '.', "."},
        {"glVertex3d", pnames2743, '.', "..."},
        {"glVertex3dv", pnames2744, '.', "."},
        {"glVertex3f", pnames2745, '.', "..."},
        {"glVertex3fv", pnames2746, '.', "."},
        {"glVertex3hNV", pnames2747, '.', "..."},
        {"glVertex3hvNV", pnames2748, '.', "."},
        {"glVertex3i", pnames2749, '.', "..."},
        {"glVertex3iv", pnames2750, '.', "."},
        {"glVertex3s", pnames2751, '.', "..."},
        {"glVertex3sv", pnames2752, '.', "."},
        {"glVertex3xOES", pnames2753, '.', ".."},
        {"glVertex3xvOES", pnames2754, '.', "."},
        {"glVertex4bOES", pnames2755, '.', "...."},
        {"glVertex4bvOES", pnames2756, '.', "."},
        {"glVertex4d", pnames2757, '.', "...."},
        {"glVertex4dv", pnames2758, '.', "."},
        {"glVertex4f", pnames2759, '.', "...."},
        {"glVertex4fv", pnames2760, '.', "."},
        {"glVertex4hNV", pnames2761, '.', "...."},
        {"glVertex4hvNV", pnames2762, '.', "."},
        {"glVertex4i", pnames2763, '.', "...."},
        {"glVertex4iv", pnames2764, '.', "."},
        {"glVertex4s", pnames2765, '.', "...."},
        {"glVertex4sv", pnames2766, '.', "."},
        {"glVertex4xOES", pnames2767, '.', "..."},
        {"glVertex4xvOES", pnames2768, '.', "."},
        {"glVertexArrayAttribBinding", pnames2769, '.', "..."},
        {"glVertexArrayAttribFormat", pnames2770, '.', "...EB."},
        {"glVertexArrayAttribIFormat", pnames2771, '.', "...E."},
        {"glVertexArrayAttribLFormat", pnames2772, '.', "...E."},
        {"glVertexArrayBindVertexBufferEXT", pnames2773, '.', "....."},
        {"glVertexArrayBindingDivisor", pnames2774, '.', "..."},
        {"glVertexArrayColorOffsetEXT", pnames2775, '.', "...E.."},
        {"glVertexArrayEdgeFlagOffsetEXT", pnames2776, '.', "...."},
        {"glVertexArrayElementBuffer", pnames2777, '.', ".."},
        {"glVertexArrayFogCoordOffsetEXT", pnames2778, '.', "..E.."},
        {"glVertexArrayIndexOffsetEXT", pnames2779, '.', "..E.."},
        {"glVertexArrayMultiTexCoordOffsetEXT", pnames2780, '.', "..E.E.."},
        {"glVertexArrayNormalOffsetEXT", pnames2781, '.', "..E.."},
        {"glVertexArrayParameteriAPPLE", pnames2782, '.', "E."},
        {"glVertexArrayRangeAPPLE", pnames2783, '.', ".."},
        {"glVertexArrayRangeNV", pnames2784, '.', ".."},
        {"glVertexArraySecondaryColorOffsetEXT", pnames2785, '.', "...E.."},
        {"glVertexArrayTexCoordOffsetEXT", pnames2786, '.', "...E.."},
        {"glVertexArrayVertexAttribBindingEXT", pnames2787, '.', "..."},
        {"glVertexArrayVertexAttribDivisorEXT", pnames2788, '.', "..."},
        {"glVertexArrayVertexAttribFormatEXT", pnames2789, '.', "...EB."},
        {"glVertexArrayVertexAttribIFormatEXT", pnames2790, '.', "...E."},
        {"glVertexArrayVertexAttribIOffsetEXT", pnames2791, '.', "....E.."},
        {"glVertexArrayVertexAttribLFormatEXT", pnames2792, '.', "...E."},
        {"glVertexArrayVertexAttribLOffsetEXT", pnames2793, '.', "....E.."},
        {"glVertexArrayVertexAttribOffsetEXT", pnames2794, '.', "....EB.."},
        {"glVertexArrayVertexBindingDivisorEXT", pnames2795, '.', "..."},
        {"glVertexArrayVertexBuffer", pnames2796, '.', "....."},
        {"glVertexArrayVertexBuffers", pnames2797, '.', "......"},
        {"glVertexArrayVertexOffsetEXT", pnames2798, '.', "...E.."},
        {"glVertexAttrib1d", pnames2799, '.', ".."},
        {"glVertexAttrib1dARB", pnames2800, '.', ".."},
        {"glVertexAttrib1dNV", pnames2801, '.', ".."},
        {"glVertexAttrib1dv", pnames2802, '.', ".."},
        {"glVertexAttrib1dvARB", pnames2803, '.', ".."},
        {"glVertexAttrib1dvNV", pnames2804, '.', ".."},
        {"glVertexAttrib1f", pnames2805, '.', ".."},
        {"glVertexAttrib1fARB", pnames2806, '.', ".."},
        {"glVertexAttrib1fNV", pnames2807, '.', ".."},
        {"glVertexAttrib1fv", pnames2808, '.', ".."},
        {"glVertexAttrib1fvARB", pnames2809, '.', ".."},
        {"glVertexAttrib1fvNV", pnames2810, '.', ".."},
        {"glVertexAttrib1hNV", pnames2811, '.', ".."},
        {"glVertexAttrib1hvNV", pnames2812, '.', ".."},
        {"glVertexAttrib1s", pnames2813, '.', ".."},
        {"glVertexAttrib1sARB", pnames2814, '.', ".."},
        {"glVertexAttrib1sNV", pnames2815, '.', ".."},
        {"glVertexAttrib1sv", pnames2816, '.', ".."},
        {"glVertexAttrib1svARB", pnames2817, '.', ".."},
        {"glVertexAttrib1svNV", pnames2818, '.', ".."},
        {"glVertexAttrib2d", pnames2819, '.', "..."},
        {"glVertexAttrib2dARB", pnames2820, '.', "..."},
        {"glVertexAttrib2dNV", pnames2821, '.', "..."},
        {"glVertexAttrib2dv", pnames2822, '.', ".."},
        {"glVertexAttrib2dvARB", pnames2823, '.', ".."},
        {"glVertexAttrib2dvNV", pnames2824, '.', ".."},
        {"glVertexAttrib2f", pnames2825, '.', "..."},
        {"glVertexAttrib2fARB", pnames2826, '.', "..."},
        {"glVertexAttrib2fNV", pnames2827, '.', "..."},
        {"glVertexAttrib2fv", pnames2828, '.', ".."},
        {"glVertexAttrib2fvARB", pnames2829, '.', ".."},
        {"glVertexAttrib2fvNV", pnames2830, '.', ".."},
        {"glVertexAttrib2hNV", pnames2831, '.', "..."},
        {"glVertexAttrib2hvNV", pnames2832, '.', ".."},
        {"glVertexAttrib2s", pnames2833, '.', "..."},
        {"glVertexAttrib2sARB", pnames2834, '.', "..."},
        {"glVertexAttrib2sNV", pnames2835, '.', "..."},
        {"glVertexAttrib2sv", pnames2836, '.', ".."},
        {"glVertexAttrib2svARB", pnames2837, '.', ".."},
        {"glVertexAttrib2svNV", pnames2838, '.', ".."},
        {"glVertexAttrib3d", pnames2839, '.', "...."},
        {"glVertexAttrib3dARB", pnames2840, '.', "...."},
        {"glVertexAttrib3dNV", pnames2841, '.', "...."},
        {"glVertexAttrib3dv", pnames2842, '.', ".."},
        {"glVertexAttrib3dvARB", pnames2843, '.', ".."},
        {"glVertexAttrib3dvNV", pnames2844, '.', ".."},
        {"glVertexAttrib3f", pnames2845, '.', "...."},
        {"glVertexAttrib3fARB", pnames2846, '.', "...."},
        {"glVertexAttrib3fNV", pnames2847, '.', "...."},
        {"glVertexAttrib3fv", pnames2848, '.', ".."},
        {"glVertexAttrib3fvARB", pnames2849, '.', ".."},
        {"glVertexAttrib3fvNV", pnames2850, '.', ".."},
        {"glVertexAttrib3hNV", pnames2851, '.', "...."},
        {"glVertexAttrib3hvNV", pnames2852, '.', ".."},
        {"glVertexAttrib3s", pnames2853, '.', "...."},
        {"glVertexAttrib3sARB", pnames2854, '.', "...."},
        {"glVertexAttrib3sNV", pnames2855, '.', "...."},
        {"glVertexAttrib3sv", pnames2856, '.', ".."},
        {"glVertexAttrib3svARB", pnames2857, '.', ".."},
        {"glVertexAttrib3svNV", pnames2858, '.', ".."},
        {"glVertexAttrib4Nbv", pnames2859, '.', ".."},
        {"glVertexAttrib4NbvARB", pnames2860, '.', ".."},
        {"glVertexAttrib4Niv", pnames2861, '.', ".."},
        {"glVertexAttrib4NivARB", pnames2862, '.', ".."},
        {"glVertexAttrib4Nsv", pnames2863, '.', ".."},
        {"glVertexAttrib4NsvARB", pnames2864, '.', ".."},
        {"glVertexAttrib4Nub", pnames2865, '.', "....."},
        {"glVertexAttrib4NubARB", pnames2866, '.', "....."},
        {"glVertexAttrib4Nubv", pnames2867, '.', ".."},
        {"glVertexAttrib4NubvARB", pnames2868, '.', ".."},
        {"glVertexAttrib4Nuiv", pnames2869, '.', ".."},
        {"glVertexAttrib4NuivARB", pnames2870, '.', ".."},
        {"glVertexAttrib4Nusv", pnames2871, '.', ".."},
        {"glVertexAttrib4NusvARB", pnames2872, '.', ".."},
        {"glVertexAttrib4bv", pnames2873, '.', ".."},
        {"glVertexAttrib4bvARB", pnames2874, '.', ".."},
        {"glVertexAttrib4d", pnames2875, '.', "....."},
        {"glVertexAttrib4dARB", pnames2876, '.', "....."},
        {"glVertexAttrib4dNV", pnames2877, '.', "....."},
        {"glVertexAttrib4dv", pnames2878, '.', ".."},
        {"glVertexAttrib4dvARB", pnames2879, '.', ".."},
        {"glVertexAttrib4dvNV", pnames2880, '.', ".."},
        {"glVertexAttrib4f", pnames2881, '.', "....."},
        {"glVertexAttrib4fARB", pnames2882, '.', "....."},
        {"glVertexAttrib4fNV", pnames2883, '.', "....."},
        {"glVertexAttrib4fv", pnames2884, '.', ".."},
        {"glVertexAttrib4fvARB", pnames2885, '.', ".."},
        {"glVertexAttrib4fvNV", pnames2886, '.', ".."},
        {"glVertexAttrib4hNV", pnames2887, '.', "....."},
        {"glVertexAttrib4hvNV", pnames2888, '.', ".."},
        {"glVertexAttrib4iv", pnames2889, '.', ".."},
        {"glVertexAttrib4ivARB", pnames2890, '.', ".."},
        {"glVertexAttrib4s", pnames2891, '.', "....."},
        {"glVertexAttrib4sARB", pnames2892, '.', "....."},
        {"glVertexAttrib4sNV", pnames2893, '.', "....."},
        {"glVertexAttrib4sv", pnames2894, '.', ".."},
        {"glVertexAttrib4svARB", pnames2895, '.', ".."},
        {"glVertexAttrib4svNV", pnames2896, '.', ".."},
        {"glVertexAttrib4ubNV", pnames2897, '.', "....."},
        {"glVertexAttrib4ubv", pnames2898, '.', ".."},
        {"glVertexAttrib4ubvARB", pnames2899, '.', ".."},
        {"glVertexAttrib4ubvNV", pnames2900, '.', ".."},
        {"glVertexAttrib4uiv", pnames2901, '.', ".."},
        {"glVertexAttrib4uivARB", pnames2902, '.', ".."},
        {"glVertexAttrib4usv", pnames2903, '.', ".."},
        {"glVertexAttrib4usvARB", pnames2904, '.', ".."},
        {"glVertexAttribArrayObjectATI", pnames2905, '.', "..EB..."},
        {"glVertexAttribBinding", pnames2906, '.', ".."},
        {"glVertexAttribDivisor", pnames2907, '.', ".."},
        {"glVertexAttribDivisorANGLE", pnames2908, '.', ".."},
        {"glVertexAttribDivisorARB", pnames2909, '.', ".."},
        {"glVertexAttribDivisorEXT", pnames2910, '.', ".."},
        {"glVertexAttribDivisorNV", pnames2911, '.', ".."},
        {"glVertexAttribFormat", pnames2912, '.', "..EB."},
        {"glVertexAttribFormatNV", pnames2913, '.', "..EB."},
        {"glVertexAttribI1i", pnames2914, '.', ".."},
        {"glVertexAttribI1iEXT", pnames2915, '.', ".."},
        {"glVertexAttribI1iv", pnames2916, '.', ".."},
        {"glVertexAttribI1ivEXT", pnames2917, '.', ".."},
        {"glVertexAttribI1ui", pnames2918, '.', ".."},
        {"glVertexAttribI1uiEXT", pnames2919, '.', ".."},
        {"glVertexAttribI1uiv", pnames2920, '.', ".."},
        {"glVertexAttribI1uivEXT", pnames2921, '.', ".."},
        {"glVertexAttribI2i", pnames2922, '.', "..."},
        {"glVertexAttribI2iEXT", pnames2923, '.', "..."},
        {"glVertexAttribI2iv", pnames2924, '.', ".."},
        {"glVertexAttribI2ivEXT", pnames2925, '.', ".."},
        {"glVertexAttribI2ui", pnames2926, '.', "..."},
        {"glVertexAttribI2uiEXT", pnames2927, '.', "..."},
        {"glVertexAttribI2uiv", pnames2928, '.', ".."},
        {"glVertexAttribI2uivEXT", pnames2929, '.', ".."},
        {"glVertexAttribI3i", pnames2930, '.', "...."},
        {"glVertexAttribI3iEXT", pnames2931, '.', "...."},
        {"glVertexAttribI3iv", pnames2932, '.', ".."},
        {"glVertexAttribI3ivEXT", pnames2933, '.', ".."},
        {"glVertexAttribI3ui", pnames2934, '.', "...."},
        {"glVertexAttribI3uiEXT", pnames2935, '.', "...."},
        {"glVertexAttribI3uiv", pnames2936, '.', ".."},
        {"glVertexAttribI3uivEXT", pnames2937, '.', ".."},
        {"glVertexAttribI4bv", pnames2938, '.', ".."},
        {"glVertexAttribI4bvEXT", pnames2939, '.', ".."},
        {"glVertexAttribI4i", pnames2940, '.', "....."},
        {"glVertexAttribI4iEXT", pnames2941, '.', "....."},
        {"glVertexAttribI4iv", pnames2942, '.', ".."},
        {"glVertexAttribI4ivEXT", pnames2943, '.', ".."},
        {"glVertexAttribI4sv", pnames2944, '.', ".."},
        {"glVertexAttribI4svEXT", pnames2945, '.', ".."},
        {"glVertexAttribI4ubv", pnames2946, '.', ".."},
        {"glVertexAttribI4ubvEXT", pnames2947, '.', ".."},
        {"glVertexAttribI4ui", pnames2948, '.', "....."},
        {"glVertexAttribI4uiEXT", pnames2949, '.', "....."},
        {"glVertexAttribI4uiv", pnames2950, '.', ".."},
        {"glVertexAttribI4uivEXT", pnames2951, '.', ".."},
        {"glVertexAttribI4usv", pnames2952, '.', ".."},
        {"glVertexAttribI4usvEXT", pnames2953, '.', ".."},
        {"glVertexAttribIFormat", pnames2954, '.', "..E."},
        {"glVertexAttribIFormatNV", pnames2955, '.', "..E."},
        {"glVertexAttribIPointer", pnames2956, '.', "..E.."},
        {"glVertexAttribIPointerEXT", pnames2957, '.', "..E.."},
        {"glVertexAttribL1d", pnames2958, '.', ".."},
        {"glVertexAttribL1dEXT", pnames2959, '.', ".."},
        {"glVertexAttribL1dv", pnames2960, '.', ".."},
        {"glVertexAttribL1dvEXT", pnames2961, '.', ".."},
        {"glVertexAttribL1i64NV", pnames2962, '.', ".."},
        {"glVertexAttribL1i64vNV", pnames2963, '.', ".."},
        {"glVertexAttribL1ui64ARB", pnames2964, '.', ".."},
        {"glVertexAttribL1ui64NV", pnames2965, '.', ".."},
        {"glVertexAttribL1ui64vARB", pnames2966, '.', ".."},
        {"glVertexAttribL1ui64vNV", pnames2967, '.', ".."},
        {"glVertexAttribL2d", pnames2968, '.', "..."},
        {"glVertexAttribL2dEXT", pnames2969, '.', "..."},
        {"glVertexAttribL2dv", pnames2970, '.', ".."},
        {"glVertexAttribL2dvEXT", pnames2971, '.', ".."},
        {"glVertexAttribL2i64NV", pnames2972, '.', "..."},
        {"glVertexAttribL2i64vNV", pnames2973, '.', ".."},
        {"glVertexAttribL2ui64NV", pnames2974, '.', "..."},
        {"glVertexAttribL2ui64vNV", pnames2975, '.', ".."},
        {"glVertexAttribL3d", pnames2976, '.', "...."},
        {"glVertexAttribL3dEXT", pnames2977, '.', "...."},
        {"glVertexAttribL3dv", pnames2978, '.', ".."},
        {"glVertexAttribL3dvEXT", pnames2979, '.', ".."},
        {"glVertexAttribL3i64NV", pnames2980, '.', "...."},
        {"glVertexAttribL3i64vNV", pnames2981, '.', ".."},
        {"glVertexAttribL3ui64NV", pnames2982, '.', "...."},
        {"glVertexAttribL3ui64vNV", pnames2983, '.', ".."},
        {"glVertexAttribL4d", pnames2984, '.', "....."},
        {"glVertexAttribL4dEXT", pnames2985, '.', "....."},
        {"glVertexAttribL4dv", pnames2986, '.', ".."},
        {"glVertexAttribL4dvEXT", pnames2987, '.', ".."},
        {"glVertexAttribL4i64NV", pnames2988, '.', "....."},
        {"glVertexAttribL4i64vNV", pnames2989, '.', ".."},
        {"glVertexAttribL4ui64NV", pnames2990, '.', "....."},
        {"glVertexAttribL4ui64vNV", pnames2991, '.', ".."},
        {"glVertexAttribLFormat", pnames2992, '.', "..E."},
        {"glVertexAttribLFormatNV", pnames2993, '.', "..E."},
        {"glVertexAttribLPointer", pnames2994, '.', "..E.."},
        {"glVertexAttribLPointerEXT", pnames2995, '.', "..E.."},
        {"glVertexAttribP1ui", pnames2996, '.', ".EB."},
        {"glVertexAttribP1uiv", pnames2997, '.', ".EB."},
        {"glVertexAttribP2ui", pnames2998, '.', ".EB."},
        {"glVertexAttribP2uiv", pnames2999, '.', ".EB."},
        {"glVertexAttribP3ui", pnames3000, '.', ".EB."},
        {"glVertexAttribP3uiv", pnames3001, '.', ".EB."},
        {"glVertexAttribP4ui", pnames3002, '.', ".EB."},
        {"glVertexAttribP4uiv", pnames3003, '.', ".EB."},
        {"glVertexAttribParameteriAMD", pnames3004, '.', ".E."},
        {"glVertexAttribPointer", pnames3005, '.', "..EB.."},
        {"glVertexAttribPointerARB", pnames3006, '.', "..EB.."},
        {"glVertexAttribPointerNV", pnames3007, '.', "..E.."},
        {"glVertexAttribs1dvNV", pnames3008, '.', "..."},
        {"glVertexAttribs1fvNV", pnames3009, '.', "..."},
        {"glVertexAttribs1hvNV", pnames3010, '.', "..."},
        {"glVertexAttribs1svNV", pnames3011, '.', "..."},
        {"glVertexAttribs2dvNV", pnames3012, '.', "..."},
        {"glVertexAttribs2fvNV", pnames3013, '.', "..."},
        {"glVertexAttribs2hvNV", pnames3014, '.', "..."},
        {"glVertexAttribs2svNV", pnames3015, '.', "..."},
        {"glVertexAttribs3dvNV", pnames3016, '.', "..."},
        {"glVertexAttribs3fvNV", pnames3017, '.', "..."},
        {"glVertexAttribs3hvNV", pnames3018, '.', "..."},
        {"glVertexAttribs3svNV", pnames3019, '.', "..."},
        {"glVertexAttribs4dvNV", pnames3020, '.', "..."},
        {"glVertexAttribs4fvNV", pnames3021, '.', "..."},
        {"glVertexAttribs4hvNV", pnames3022, '.', "..."},
        {"glVertexAttribs4svNV", pnames3023, '.', "..."},
        {"glVertexAttribs4ubvNV", pnames3024, '.', "..."},
        {"glVertexBindingDivisor", pnames3025, '.', ".."},
        {"glVertexBlendARB", pnames3026, '.', "."},
        {"glVertexBlendEnvfATI", pnames3027, '.', "E."},
        {"glVertexBlendEnviATI", pnames3028, '.', "E."},
        {"glVertexFormatNV", pnames3029, '.', ".E."},
        {"glVertexP2ui", pnames3030, '.', "E."},
        {"glVertexP2uiv", pnames3031, '.', "E."},
        {"glVertexP3ui", pnames3032, '.', "E."},
        {"glVertexP3uiv", pnames3033, '.', "E."},
        {"glVertexP4ui", pnames3034, '.', "E."},
        {"glVertexP4uiv", pnames3035, '.', "E."},
        {"glVertexPointer", pnames3036, '.', ".E.."},
        {"glVertexPointerEXT", pnames3037, '.', ".E..."},
        {"glVertexPointerListIBM", pnames3038, '.', ".E..."},
        {"glVertexPointervINTEL", pnames3039, '.', ".E."},
        {"glVertexStream1dATI", pnames3040, '.', "E."},
        {"glVertexStream1dvATI", pnames3041, '.', "E."},
        {"glVertexStream1fATI", pnames3042, '.', "E."},
        {"glVertexStream1fvATI", pnames3043, '.', "E."},
        {"glVertexStream1iATI", pnames3044, '.', "E."},
        {"glVertexStream1ivATI", pnames3045, '.', "E."},
        {"glVertexStream1sATI", pnames3046, '.', "E."},
        {"glVertexStream1svATI", pnames3047, '.', "E."},
        {"glVertexStream2dATI", pnames3048, '.', "E.."},
        {"glVertexStream2dvATI", pnames3049, '.', "E."},
        {"glVertexStream2fATI", pnames3050, '.', "E.."},
        {"glVertexStream2fvATI", pnames3051, '.', "E."},
        {"glVertexStream2iATI", pnames3052, '.', "E.."},
        {"glVertexStream2ivATI", pnames3053, '.', "E."},
        {"glVertexStream2sATI", pnames3054, '.', "E.."},
        {"glVertexStream2svATI", pnames3055, '.', "E."},
        {"glVertexStream3dATI", pnames3056, '.', "E..."},
        {"glVertexStream3dvATI", pnames3057, '.', "E."},
        {"glVertexStream3fATI", pnames3058, '.', "E..."},
        {"glVertexStream3fvATI", pnames3059, '.', "E."},
        {"glVertexStream3iATI", pnames3060, '.', "E..."},
        {"glVertexStream3ivATI", pnames3061, '.', "E."},
        {"glVertexStream3sATI", pnames3062, '.', "E..."},
        {"glVertexStream3svATI", pnames3063, '.', "E."},
        {"glVertexStream4dATI", pnames3064, '.', "E...."},
        {"glVertexStream4dvATI", pnames3065, '.', "E."},
        {"glVertexStream4fATI", pnames3066, '.', "E...."},
        {"glVertexStream4fvATI", pnames3067, '.', "E."},
        {"glVertexStream4iATI", pnames3068, '.', "E...."},
        {"glVertexStream4ivATI", pnames3069, '.', "E."},
        {"glVertexStream4sATI", pnames3070, '.', "E...."},
        {"glVertexStream4svATI", pnames3071, '.', "E."},
        {"glVertexWeightPointerEXT", pnames3072, '.', ".E.."},
        {"glVertexWeightfEXT", pnames3073, '.', "."},
        {"glVertexWeightfvEXT", pnames3074, '.', "."},
        {"glVertexWeighthNV", pnames3075, '.', "."},
        {"glVertexWeighthvNV", pnames3076, '.', "."},
        {"glVideoCaptureNV", pnames3077, 'E', "..."},
        {"glVideoCaptureStreamParameterdvNV", pnames3078, '.', "..E."},
        {"glVideoCaptureStreamParameterfvNV", pnames3079, '.', "..E."},
        {"glVideoCaptureStreamParameterivNV", pnames3080, '.', "..E."},
        {"glViewport", pnames3081, '.', "...."},
        {"glViewportArrayv", pnames3082, '.', "..."},
        {"glViewportArrayvNV", pnames3083, '.', "..."},
        {"glViewportArrayvOES", pnames3084, '.', "..."},
        {"glViewportIndexedf", pnames3085, '.', "....."},
        {"glViewportIndexedfOES", pnames3086, '.', "....."},
        {"glViewportIndexedfNV", pnames3087, '.', "....."},
        {"glViewportIndexedfv", pnames3088, '.', ".."},
        {"glViewportIndexedfvOES", pnames3089, '.', ".."},
        {"glViewportIndexedfvNV", pnames3090, '.', ".."},
        {"glViewportPositionWScaleNV", pnames3091, '.', "..."},
        {"glViewportSwizzleNV", pnames3092, '.', ".EEEE"},
        {"glWaitSync", pnames3093, '.', ".F."},
        {"glWaitSyncAPPLE", pnames3094, '.', ".F."},
        {"glWeightPathsNV", pnames3095, '.', "...."},
        {"glWeightPointerARB", pnames3096, '.', ".E.."},
        {"glWeightPointerOES", pnames3097, '.', ".E.."},
        {"glWeightbvARB", pnames3098, '.', ".."},
        {"glWeightdvARB", pnames3099, '.', ".."},
        {"glWeightfvARB", pnames3100, '.', ".."},
        {"glWeightivARB", pnames3101, '.', ".."},
        {"glWeightsvARB", pnames3102, '.', ".."},
        {"glWeightubvARB", pnames3103, '.', ".."},
        {"glWeightuivARB", pnames3104, '.', ".."},
        {"glWeightusvARB", pnames3105, '.', ".."},
        {"glWindowPos2d", pnames3106, '.', ".."},
        {"glWindowPos2dARB", pnames3107, '.', ".."},
        {"glWindowPos2dMESA", pnames3108, '.', ".."},
        {"glWindowPos2dv", pnames3109, '.', "."},
        {"glWindowPos2dvARB", pnames3110, '.', "."},
        {"glWindowPos2dvMESA", pnames3111, '.', "."},
        {"glWindowPos2f", pnames3112, '.', ".."},
        {"glWindowPos2fARB", pnames3113, '.', ".."},
        {"glWindowPos2fMESA", pnames3114, '.', ".."},
        {"glWindowPos2fv", pnames3115, '.', "."},
        {"glWindowPos2fvARB", pnames3116, '.', "."},
        {"glWindowPos2fvMESA", pnames3117, '.', "."},
        {"glWindowPos2i", pnames3118, '.', ".."},
        {"glWindowPos2iARB", pnames3119, '.', ".."},
        {"glWindowPos2iMESA", pnames3120, '.', ".."},
        {"glWindowPos2iv", pnames3121, '.', "."},
        {"glWindowPos2ivARB", pnames3122, '.', "."},
        {"glWindowPos2ivMESA", pnames3123, '.', "."},
        {"glWindowPos2s", pnames3124, '.', ".."},
        {"glWindowPos2sARB", pnames3125, '.', ".."},
        {"glWindowPos2sMESA", pnames3126, '.', ".."},
        {"glWindowPos2sv", pnames3127, '.', "."},
        {"glWindowPos2svARB", pnames3128, '.', "."},
        {"glWindowPos2svMESA", pnames3129, '.', "."},
        {"glWindowPos3d", pnames3130, '.', "..."},
        {"glWindowPos3dARB", pnames3131, '.', "..."},
        {"glWindowPos3dMESA", pnames3132, '.', "..."},
        {"glWindowPos3dv", pnames3133, '.', "."},
        {"glWindowPos3dvARB", pnames3134, '.', "."},
        {"glWindowPos3dvMESA", pnames3135, '.', "."},
        {"glWindowPos3f", pnames3136, '.', "..."},
        {"glWindowPos3fARB", pnames3137, '.', "..."},
        {"glWindowPos3fMESA", pnames3138, '.', "..."},
        {"glWindowPos3fv", pnames3139, '.', "."},
        {"glWindowPos3fvARB", pnames3140, '.', "."},
        {"glWindowPos3fvMESA", pnames3141, '.', "."},
        {"glWindowPos3i", pnames3142, '.', "..."},
        {"glWindowPos3iARB", pnames3143, '.', "..."},
        {"glWindowPos3iMESA", pnames3144, '.', "..."},
        {"glWindowPos3iv", pnames3145, '.', "."},
        {"glWindowPos3ivARB", pnames3146, '.', "."},
        {"glWindowPos3ivMESA", pnames3147, '.', "."},
        {"glWindowPos3s", pnames3148, '.', "..."},
        {"glWindowPos3sARB", pnames3149, '.', "..."},
        {"glWindowPos3sMESA", pnames3150, '.', "..."},
        {"glWindowPos3sv", pnames3151, '.', "."},
        {"glWindowPos3svARB", pnames3152, '.', "."},
        {"glWindowPos3svMESA", pnames3153, '.', "."},
        {"glWindowPos4dMESA", pnames3154, '.', "...."},
        {"glWindowPos4dvMESA", pnames3155, '.', "."},
        {"glWindowPos4fMESA", pnames3156, '.', "...."},
        {"glWindowPos4fvMESA", pnames3157, '.', "."},
        {"glWindowPos4iMESA", pnames3158, '.', "...."},
        {"glWindowPos4ivMESA", pnames3159, '.', "."},
        {"glWindowPos4sMESA", pnames3160, '.', "...."},
        {"glWindowPos4svMESA", pnames3161, '.', "."},
        {"glWindowRectanglesEXT", pnames3162, '.', "E.."},
        {"glWriteMaskEXT", pnames3163, '.', "..EEEE"},
    };
    return ret[index];
}
