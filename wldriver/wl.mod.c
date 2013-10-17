#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x68d372d2, "module_layout" },
	{ 0x402b8281, "__request_module" },
	{ 0x794a2c29, "kmalloc_caches" },
	{ 0x12da5bb2, "__kmalloc" },
	{ 0xe8304a3d, "mem_map" },
	{ 0x76ebea8, "pv_lock_ops" },
	{ 0x349cba85, "strchr" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0xc996d097, "del_timer" },
	{ 0xd0d8621b, "strlen" },
	{ 0x9f9f8038, "dev_set_drvdata" },
	{ 0x38dd7f9f, "pci_disable_device" },
	{ 0xa4eb4eff, "_raw_spin_lock_bh" },
	{ 0x9a530e3c, "skb_clone" },
	{ 0x8949858b, "schedule_work" },
	{ 0x64063398, "remove_proc_entry" },
	{ 0x51e5e67d, "filp_close" },
	{ 0x2b3d0d5, "x86_dma_fallback_dev" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0x25277497, "rfkill_register" },
	{ 0x91715312, "sprintf" },
	{ 0x7d11c268, "jiffies" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x810b3618, "param_ops_string" },
	{ 0x6d57ee8f, "netif_rx" },
	{ 0xb2a006d5, "kernel_read" },
	{ 0xc18b0d86, "pci_set_master" },
	{ 0x2bc95bd4, "memset" },
	{ 0x17c09ec5, "dev_alloc_skb" },
	{ 0xd7001850, "pci_restore_state" },
	{ 0xf97456ea, "_raw_spin_unlock_irqrestore" },
	{ 0xfe20430f, "rfkill_alloc" },
	{ 0x50eedeb8, "printk" },
	{ 0x5152e605, "memcmp" },
	{ 0x97999817, "rfkill_set_hw_state" },
	{ 0xfaef0ed, "__tasklet_schedule" },
	{ 0xb6ed1e53, "strncpy" },
	{ 0x2f287f0d, "copy_to_user" },
	{ 0x29e9c274, "register_netdev" },
	{ 0xb4390f9a, "mcount" },
	{ 0xa894f159, "wireless_send_event" },
	{ 0x6c2e3320, "strncmp" },
	{ 0x16305289, "warn_slowpath_null" },
	{ 0xc399d533, "pci_bus_write_config_dword" },
	{ 0x9314688b, "skb_push" },
	{ 0x9545af6d, "tasklet_init" },
	{ 0xbe2c0274, "add_timer" },
	{ 0xc0d39b77, "dma_release_from_coherent" },
	{ 0x2072ee9b, "request_threaded_irq" },
	{ 0xa094649, "skb_pull" },
	{ 0x98602ed7, "dev_kfree_skb_any" },
	{ 0xcb502c92, "dma_alloc_from_coherent" },
	{ 0x82072614, "tasklet_kill" },
	{ 0xe903c01, "lib80211_get_crypto_ops" },
	{ 0xc6cbbc89, "capable" },
	{ 0x9f984513, "strrchr" },
	{ 0x42c8de35, "ioremap_nocache" },
	{ 0xaad6d92f, "rfkill_init_sw_state" },
	{ 0xc7a148fd, "pci_bus_read_config_dword" },
	{ 0x8bf826c, "_raw_spin_unlock_bh" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x4292364c, "schedule" },
	{ 0xe75972db, "alloc_netdev_mqs" },
	{ 0x829ff995, "pv_cpu_ops" },
	{ 0x564349ca, "eth_type_trans" },
	{ 0x829b533d, "create_proc_entry" },
	{ 0x22baf9f7, "pci_unregister_driver" },
	{ 0xe8823b16, "ether_setup" },
	{ 0x3f9b9190, "kmem_cache_alloc_trace" },
	{ 0x67f7403e, "_raw_spin_lock" },
	{ 0x21fb443e, "_raw_spin_lock_irqsave" },
	{ 0x7afa89fc, "vsnprintf" },
	{ 0x50cd4c20, "pci_set_power_state" },
	{ 0x37a0cba, "kfree" },
	{ 0xdb68bbad, "rfkill_destroy" },
	{ 0x2e60bace, "memcpy" },
	{ 0xedc03953, "iounmap" },
	{ 0x2a75035a, "__pci_register_driver" },
	{ 0x5e98ec96, "unregister_netdev" },
	{ 0xb81960ca, "snprintf" },
	{ 0x6c875264, "__netif_schedule" },
	{ 0x8235805b, "memmove" },
	{ 0xa51a27a6, "consume_skb" },
	{ 0x388a3a4, "skb_put" },
	{ 0x83eb21c, "rfkill_unregister" },
	{ 0x6468ccc, "pci_enable_device" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x2482e688, "vsprintf" },
	{ 0xec51d6a4, "dev_get_drvdata" },
	{ 0x9e7d6bd0, "__udelay" },
	{ 0xbb064e58, "dma_ops" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xb4372f24, "pci_save_state" },
	{ 0xe914e41e, "strcpy" },
	{ 0x10de19c6, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lib80211";

MODULE_ALIAS("pci:v000014E4d00004311sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004312sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004313sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004315sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004328sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004329sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000432Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000432Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000432Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000432Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004353sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000A99Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004357sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004727sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004358sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004359sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000435Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00000576sv*sd*bc*sc*i*");

MODULE_INFO(srcversion, "12608FA2F7270DB96BBC3A9");
