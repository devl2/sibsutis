import React, { useState, useEffect } from 'react';
import axios from 'axios';
import {
  Table,
  TableBody,
  TableCell,
  TableContainer,
  TableHead,
  TableRow,
  Paper,
  TextField,
  Select,
  MenuItem,
  FormControl,
  InputLabel,
  Button,
  Box,
  Grid,
  TablePagination,
  Chip
} from '@mui/material';
import DatePicker from 'react-datepicker';
import 'react-datepicker/dist/react-datepicker.css';

const LogsViewer = () => {
  const [logs, setLogs] = useState([]);
  const [totalCount, setTotalCount] = useState(0);
  const [page, setPage] = useState(0);
  const [rowsPerPage, setRowsPerPage] = useState(20);
  const [search, setSearch] = useState('');
  const [level, setLevel] = useState('');
  const [source, setSource] = useState('');
  const [fromDate, setFromDate] = useState(null);
  const [toDate, setToDate] = useState(null);
  const [loading, setLoading] = useState(false);
  
  const API_BASE_URL = 'http://localhost:5065';
  const LOGS_API_URL = `${API_BASE_URL}/api/logs/debug`;

  const levels = ['Information', 'Warning', 'Error', 'Debug'];
  const sources = ['Program','CommentApi', 'Database'];

  useEffect(() => {
    fetchLogs();
  }, [page, rowsPerPage, search, level, source, fromDate, toDate]);

  const fetchLogs = async () => {
    setLoading(true);
    try {
      const params = {
        page: page + 1,
        pageSize: rowsPerPage,
        search: search || undefined,
        level: level || undefined,
        source: source || undefined,
        fromDate: fromDate?.toISOString(),
        toDate: toDate?.toISOString(),
      };
  
      console.log('Sending request to:', LOGS_API_URL, 'with params:', params);
  
      const response = await axios.get(LOGS_API_URL, { params });
      console.log('Response data:', response.data);
  
      if (!response.data) {
        throw new Error('Empty response from server');
      }

      setLogs(response.data.logs || []);
      setTotalCount(response.data.count || 0);
    } catch (error) {
      console.error('Error fetching logs:', error);
    } finally {
      setLoading(false);
    }
  };
  
  const handleChangePage = (event, newPage) => {
    setPage(newPage);
  };

  const handleChangeRowsPerPage = (event) => {
    setRowsPerPage(parseInt(event.target.value, 10));
    setPage(0);
  };

  const handleResetFilters = () => {
    setSearch('');
    setLevel('');
    setSource('');
    setFromDate(null);
    setToDate(null);
    setPage(0);
  };

  const getLevelColor = (level) => {
    switch (level) {
      case 'Error':
      case 'Critical':
        return 'error';
      case 'Warning':
        return 'warning';
      case 'Information':
        return 'info';
      default:
        return 'default';
    }
  };

  return (
    <Paper sx={{ p: 2 }}>
      <Box sx={{ mb: 3 }}>
        <Grid container spacing={2}>
          <Grid size={{ xs: 12, sm: 6, md: 3 }}>
            <TextField
              fullWidth
              label="Search"
              value={search}
              onChange={(e) => setSearch(e.target.value)}
              variant="outlined"
            />
          </Grid>
          <Grid size={{ xs: 12, sm: 6, md: 2 }}>
            <FormControl fullWidth>
              <InputLabel>Level</InputLabel>
              <Select
                value={level}
                onChange={(e) => setLevel(e.target.value)}
                label="Level"
              >
                <MenuItem value=""><em>All</em></MenuItem>
                {levels.map((lvl) => (
                  <MenuItem key={lvl} value={lvl}>{lvl}</MenuItem>
                ))}
              </Select>
            </FormControl>
          </Grid>
          <Grid size={{ xs: 12, sm: 6, md: 2 }}>
            <FormControl fullWidth>
              <InputLabel>Source</InputLabel>
              <Select
                value={source}
                onChange={(e) => setSource(e.target.value)}
                label="Source"
              >
                <MenuItem value=""><em>All</em></MenuItem>
                {sources.map((src) => (
                  <MenuItem key={src} value={src}>{src}</MenuItem>
                ))}
              </Select>
            </FormControl>
          </Grid>
          <Grid size={{ xs: 12, sm: 6, md: 2 }}>
            <DatePicker
              selected={fromDate}
              onChange={(date) => setFromDate(date)}
              selectsStart
              startDate={fromDate}
              endDate={toDate}
              placeholderText="From date"
              className="date-picker"
            />
          </Grid>
          <Grid size={{ xs: 12, sm: 6, md: 2 }}>
            <DatePicker
              selected={toDate}
              onChange={(date) => setToDate(date)}
              selectsEnd
              startDate={fromDate}
              endDate={toDate}
              minDate={fromDate}
              placeholderText="To date"
              className="date-picker"
            />
          </Grid>
          <Grid size={{ xs: 12, sm: 6, md: 1 }}>
            <Button
              fullWidth
              variant="outlined"
              onClick={handleResetFilters}
              sx={{ height: '56px' }}
            >
              Reset
            </Button>
          </Grid>
        </Grid>
      </Box>

      <TableContainer component={Paper}>
        <Table>
          <TableHead>
            <TableRow>
              <TableCell>Timestamp</TableCell>
              <TableCell>Level</TableCell>
              <TableCell>Source</TableCell>
              <TableCell>Message</TableCell>
              <TableCell>Request Path</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {loading ? (
              <TableRow>
                <TableCell colSpan={5} align="center">Loading...</TableCell>
              </TableRow>
            ) : logs.length === 0 ? (
              <TableRow>
                <TableCell colSpan={5} align="center">No logs found</TableCell>
              </TableRow>
            ) : (
              logs.map((log) => (
                <TableRow key={log.id}>
                  <TableCell>{new Date(log.timestamp).toLocaleString()}</TableCell>
                  <TableCell>
                    <Chip 
                      label={log.level} 
                      color={getLevelColor(log.level)} 
                      size="small" 
                    />
                  </TableCell>
                  <TableCell>{log.source}</TableCell>
                  <TableCell style={{ whiteSpace: 'pre-wrap' }}>
                    {log.message}
                    {log.exception && (
                      <div style={{ color: 'red', marginTop: '5px' }}>
                        {log.exception}
                      </div>
                    )}
                  </TableCell>
                  <TableCell>{log.requestPath}</TableCell>
                </TableRow>
              ))
            )}
          </TableBody>
        </Table>
      </TableContainer>

      <TablePagination
        rowsPerPageOptions={[10, 20, 50, 100]}
        component="div"
        count={totalCount}
        rowsPerPage={rowsPerPage}
        page={page}
        onPageChange={handleChangePage}
        onRowsPerPageChange={handleChangeRowsPerPage}
      />
    </Paper>
  );
};

export default LogsViewer;