-- .nvim.lua

-- Automatically start/attach LSP when opening C++ or C files
vim.api.nvim_create_autocmd("FileType", {
  pattern = { "cpp", "c", "hpp", "h" },
  callback = function(args)
    vim.lsp.start({
      name = "clangd",
      cmd = { "clangd" },
      root_dir = vim.fn.getcwd(), -- Sets project root to current working directory
    })

    -- Quick keymaps for this buffer
    local opts = { buffer = args.buf }
    vim.keymap.set("n", "gd", vim.lsp.buf.definition, opts)
    vim.keymap.set("n", "K",  vim.lsp.buf.hover, opts)
    vim.keymap.set("n", "<leader>rn", vim.lsp.buf.rename, opts)
    vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action, opts)
  end,
})
